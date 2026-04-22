// StartScreen.cpp
// Runs on MSPM0G3507
// Blocking start screen: splash -> language select -> return chosen language.
// SW1 (PA27, bit 0) advances / confirms. SW2 (PA28, bit 1) resets to splash.
#include "StartScreen.h"
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "Switch.h"
#include "Sound.h"

extern GameLanguage_t lang;

// ---- internal helpers -------------------------------------------------------

// Polls switches every 20 ms; returns 1 on SW1 rising edge, 2 on SW2 rising edge.
static uint32_t WaitForSwitch(void) {
  uint32_t last = Switch_In();
  while (1) {
    Clock_Delay1ms(20);
    uint32_t now = Switch_In();
    if (!(last & 0x01) && (now & 0x01)) return 1;
    if (!(last & 0x02) && (now & 0x02)) return 2;
    last = now;
  }
}

static void DrawSplash(void) {
  ST7735_FillScreen(ST7735_BLACK);

  ST7735_SetTextColor(ST7735_YELLOW);
  if(!lang) {ST7735_SetCursor(5, 2); ST7735_OutString((char *)"RACING GAME");}
  else {ST7735_SetCursor(3, 2); ST7735_OutString((char *) "Juego de Carreras");}

  ST7735_SetTextColor(ST7735_CYAN);
  ST7735_SetCursor(3, 4);
  if(!lang) ST7735_OutString((char *)"Drive or die.");
  else ST7735_OutString((char *) "Conduce o Muere.");

  ST7735_SetTextColor(ST7735_WHITE);
  ST7735_SetCursor(1, 9);
  ST7735_OutString((char *)"-------------------");

  ST7735_SetTextColor(ST7735_GREEN);
  ST7735_SetCursor(1, 11);
  if(!lang) ST7735_OutString((char *)"SW1 = Start");
  else ST7735_OutString((char *) "SW1 = Comenzar");

  ST7735_SetTextColor(ST7735_RED);
  ST7735_SetCursor(1, 13);
  if(!lang) ST7735_OutString((char *)"SW2 = Reset");
  else ST7735_OutString((char *) "SW2 = Reiniciar");
}

// Full language-select screen draw with arrow on sel (0=English, 1=Spanish).
static void DrawLanguageSelect(uint8_t sel) {
  ST7735_FillScreen(ST7735_BLACK);

  ST7735_SetTextColor(ST7735_CYAN);
  ST7735_SetCursor(2, 1);
  if(!lang) ST7735_OutString((char *)"Select Language");
  else ST7735_OutString((char *)"Seleccionar Idioma");

  ST7735_SetTextColor(ST7735_WHITE);
  ST7735_SetCursor(0, 3);
  ST7735_OutString((char *)"-------------------");

  if (sel == 0) {
    ST7735_SetTextColor(ST7735_YELLOW);
    ST7735_SetCursor(2, 6);
    if(!lang) ST7735_OutString((char *)"> English");
    else ST7735_OutString((char *)"> Ingles");
    ST7735_SetTextColor(ST7735_WHITE);
    ST7735_SetCursor(2, 8);
    if(lang) ST7735_OutString((char *)"  Espanol");
    else ST7735_OutString((char *)"  Spanish");
  } else {
    ST7735_SetTextColor(ST7735_WHITE);
    ST7735_SetCursor(2, 6);
    if(!lang) ST7735_OutString((char *)"  English");
    else ST7735_OutString((char *)"  Ingles");
    ST7735_SetTextColor(ST7735_YELLOW);
    ST7735_SetCursor(2, 8);
    if(lang) ST7735_OutString((char *)"> Espanol");
    else ST7735_OutString((char *)"> Spanish");
  }

  ST7735_SetTextColor(ST7735_WHITE);
  ST7735_SetCursor(0, 10);
  ST7735_OutString((char *)"-------------------");

  ST7735_SetTextColor(ST7735_GREEN);
  ST7735_SetCursor(1, 12);
  if(!lang) ST7735_OutString((char *)"SW1 = Confirm");
  else ST7735_OutString((char *) "SW1 = Confirmar");
  ST7735_SetTextColor(ST7735_RED);
  ST7735_SetCursor(1, 14);
  if(!lang) ST7735_OutString((char *)"SW2 = Reset");
  else ST7735_OutString((char *) "SW2 = Reiniciar");
}

// Redraws only the two option lines to move the arrow without full-screen flicker.
static void UpdateArrow(uint8_t sel) {
  if (sel == 0) {
    ST7735_SetTextColor(ST7735_YELLOW);
    ST7735_SetCursor(2, 6);
    if(!lang) ST7735_OutString((char *)"> English");
    else ST7735_OutString((char *)"> Ingles");
    ST7735_SetTextColor(ST7735_WHITE);
    ST7735_SetCursor(2, 8);
    if(lang) ST7735_OutString((char *)"  Espanol");
    else ST7735_OutString((char *)"  Spanish");
  } else {
    ST7735_SetTextColor(ST7735_WHITE);
    ST7735_SetCursor(2, 6);
    if(!lang) ST7735_OutString((char *)"  English");
    else ST7735_OutString((char *)"  Ingles");
    ST7735_SetTextColor(ST7735_YELLOW);
    ST7735_SetCursor(2, 8);
    if(lang) ST7735_OutString((char *)"> Espanol");
    else ST7735_OutString((char *)"> Spanish");
  }
}

// ---- public API -------------------------------------------------------------

GameLanguage_t StartScreen_Run(SlidePot &pot) {
  while (1) {
    // Phase 1: Splash — wait for SW1; SW2 redraws splash (already at start)
    DrawSplash();
    while (1) {
      uint32_t sw = WaitForSwitch();
      if (sw == 1) break;
      DrawSplash(); // SW2 on splash -> harmless reset to beginning
    }

    // Phase 2: Language select
    uint8_t sel = 0;
    DrawLanguageSelect(sel);

    uint32_t lastSw = Switch_In();
    while (1) {
      Clock_Delay1ms(20);

      uint8_t newSel = (pot.In() < 2048) ? 1 : 0;
      if (newSel != sel) {
        sel = newSel;
        UpdateArrow(sel);
      }

      uint32_t nowSw = Switch_In();
      if (!(lastSw & 0x01) && (nowSw & 0x01)) {
        Sound_GameStart();
        return (GameLanguage_t)sel;  // SW1 confirmed
      }
      if (!(lastSw & 0x02) && (nowSw & 0x02)) {
        break; // SW2 -> fall through to outer loop -> DrawSplash
      }
      lastSw = nowSw;
    }
  }
}
