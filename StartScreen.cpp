// StartScreen.cpp
// Runs on MSPM0G3507
// Blocking start screen: splash -> language select -> return chosen language.
// SW1 (PA27, bit 0) advances / confirms. SW2 (PA28, bit 1) resets to splash.
#include "StartScreen.h"
//#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "Switch.h"
#include "Sound.h"

#include "../SDCFilecpp/diskio.h"
#include "../SDCFilecpp/ST7735_SDC.h"
#include "../SDCFilecpp/ff.h"
#include "../SDCFilecpp/ffconf.h"
#include "../SDCFilecpp/integer.h"
extern "C" {
#include "../inc/UART.h"
}

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
  ST7735_SetCursor(5, 2);
  ST7735_OutString((char *)"RACING GAME");

  ST7735_SetTextColor(ST7735_CYAN);
  ST7735_SetCursor(3, 4);
  ST7735_OutString((char *)"Drive or die.");

  ST7735_SetTextColor(ST7735_WHITE);
  ST7735_SetCursor(0, 9);
  ST7735_OutString((char *)"-------------------");

  ST7735_SetTextColor(ST7735_GREEN);
  ST7735_SetCursor(1, 11);
  ST7735_OutString((char *)"SW1 = Start");

  ST7735_SetTextColor(ST7735_RED);
  ST7735_SetCursor(1, 13);
  ST7735_OutString((char *)"SW2 = Reset");
}

// Full language-select screen draw with arrow on sel (0=English, 1=Spanish).
static void DrawLanguageSelect(uint8_t sel) {
  ST7735_FillScreen(ST7735_BLACK);

  ST7735_SetTextColor(ST7735_CYAN);
  ST7735_SetCursor(2, 1);
  ST7735_OutString((char *)"Select Language");

  ST7735_SetTextColor(ST7735_WHITE);
  ST7735_SetCursor(0, 3);
  ST7735_OutString((char *)"-------------------");

  if (sel == 0) {
    ST7735_SetTextColor(ST7735_YELLOW);
    ST7735_SetCursor(2, 6);
    ST7735_OutString((char *)"> English");
    ST7735_SetTextColor(ST7735_WHITE);
    ST7735_SetCursor(2, 8);
    ST7735_OutString((char *)"  Espanol");
  } else {
    ST7735_SetTextColor(ST7735_WHITE);
    ST7735_SetCursor(2, 6);
    ST7735_OutString((char *)"  English");
    ST7735_SetTextColor(ST7735_YELLOW);
    ST7735_SetCursor(2, 8);
    ST7735_OutString((char *)"> Espanol");
  }

  ST7735_SetTextColor(ST7735_WHITE);
  ST7735_SetCursor(0, 10);
  ST7735_OutString((char *)"-------------------");

  ST7735_SetTextColor(ST7735_GREEN);
  ST7735_SetCursor(1, 12);
  ST7735_OutString((char *)"SW1 = Confirm");

  ST7735_SetTextColor(ST7735_RED);
  ST7735_SetCursor(1, 14);
  ST7735_OutString((char *)"SW2 = Reset");
}

// Redraws only the two option lines to move the arrow without full-screen flicker.
static void UpdateArrow(uint8_t sel) {
  if (sel == 0) {
    ST7735_SetTextColor(ST7735_YELLOW);
    ST7735_SetCursor(2, 6);
    ST7735_OutString((char *)"> English");
    ST7735_SetTextColor(ST7735_WHITE);
    ST7735_SetCursor(2, 8);
    ST7735_OutString((char *)"  Espanol");
  } else {
    ST7735_SetTextColor(ST7735_WHITE);
    ST7735_SetCursor(2, 6);
    ST7735_OutString((char *)"  English");
    ST7735_SetTextColor(ST7735_YELLOW);
    ST7735_SetCursor(2, 8);
    ST7735_OutString((char *)"> Espanol");
  }
}

// ---- public API -------------------------------------------------------------

GameLanguage_t StartScreen_Run(SlidePot &pot) {
  while (1) {
    UART_OutString((char *)"[SS] DrawSplash start\r\n");
    DrawSplash();
    UART_OutString((char *)"[SS] DrawSplash done, waiting SW1\r\n");
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

      uint8_t newSel = (pot.In() > 2048) ? 1 : 0;
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
