// Shuopu Wang's Lab9HMain.cpp
// Runs on MSPM0G3507
// Lab 9 ECE319H
// Your name
// Last Modified: January 12, 2026

#include <stdint.h>
#include <stdio.h>
#include <ti/devices/msp/msp.h>

// #include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/DAC5.h"
#include "../inc/LaunchPad.h"
#include "../inc/SlidePot.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "LED.h"
#include "SDImage.h"
#include "SmallFont.h"
#include "Sound.h"
#include "StartScreen.h"
#include "Switch.h"
#include "images/images.h"

extern "C" {
#include "../inc/UART.h"
}

#include "../SDCFilecpp/ST7735_SDC.h"
#include "../SDCFilecpp/diskio.h"
#include "../SDCFilecpp/ff.h"
#include "../SDCFilecpp/ffconf.h"
#include "../SDCFilecpp/integer.h"


extern "C" void __disable_irq(void);
extern "C" void __enable_irq(void);
extern "C" void TIMG12_IRQHandler(void);
// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void) { // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0); // run this line for 80MHz
}

uint32_t M = 1;
uint32_t Random32(void) {
  M = 1664525 * M + 1013904223;
  return M;
}
uint32_t Random(uint32_t n) { return (Random32() >> 16) % n; }

SlidePot Sensor(1500, 0); // copy calibration from Lab 7

// games  engine runs at 30Hz
void TIMG12_IRQHandler(void) {
  uint32_t pos, msg;
  if ((TIMG12->CPU_INT.IIDX) == 1) { // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
                                // game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void) {
  return (0x80 | ((GPIOB->DOUT31_0 >> 26) & 0x03));
}

typedef enum { English, Spanish, Portuguese, French } Language_t;
Language_t myLanguage = English;
typedef enum { HELLO, GOODBYE, LANGUAGE } phrase_t;
const char Hello_English[] = "Hello";
const char Hello_Spanish[] = "\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] = "All\x83";
const char Goodbye_English[] = "Goodbye";
const char Goodbye_Spanish[] = "Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[] = "English";
const char Language_Spanish[] = "Espa\xA4ol";
const char Language_Portuguese[] = "Portugu\x88s";
const char Language_French[] = "Fran\x87"
                               "ais";
const char *Phrases[3][4] = {
    {Hello_English, Hello_Spanish, Hello_Portuguese, Hello_French},
    {Goodbye_English, Goodbye_Spanish, Goodbye_Portuguese, Goodbye_French},
    {Language_English, Language_Spanish, Language_Portuguese, Language_French}};
// use main1 to observe special characters
int main1(void) { // main1
  char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(0x0000); // set screen to black
  for (int myPhrase = 0; myPhrase <= 2; myPhrase++) {
    for (int myL = 0; myL <= 3; myL++) {
      ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
      ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000); // set screen to black
  l = 128;

  IOMUX->SECCFG.PINCM[PB24INDEX] = 0x00040082;
  GPIOB->DOE31_0 |= 0x01 << 24;
  GPIOB->DOUT31_0 = 0x01 << 24;
  ;
  while (1) {

    Clock_Delay1ms(2000);
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 16; i++) {
        ST7735_SetCursor(7 * j + 0, i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7 * j + 4, i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main2(void) { // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_DrawBitmap(22, 159, PlayerShip0, 18, 8); // player ship bottom
  ST7735_DrawBitmap(53, 151, Bunker0, 18, 5);
  ST7735_DrawBitmap(42, 159, PlayerShip1, 18, 8); // player ship bottom
  ST7735_DrawBitmap(62, 159, PlayerShip2, 18, 8); // player ship bottom
  ST7735_DrawBitmap(82, 159, PlayerShip3, 18, 8); // player ship bottom
  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16, 10);
  ST7735_DrawBitmap(20, 9, SmallEnemy10pointB, 16, 10);
  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16, 10);
  ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16, 10);
  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16, 10);

  for (uint32_t t = 500; t > 0; t = t - 5) {
    SmallFont_OutVertical(t, 104, 6); // top left
    Clock_Delay1ms(50);               // delay 50 msec
  }
  ST7735_FillScreen(0x0000); // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString((char *)"GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString((char *)"Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString((char *)"Earthling!");
  ST7735_SetCursor(2, 4);
  ST7735_OutUDec(1234);
  while (1) {
  }
}

// use main3 to test switches and LEDs
int main3(void) { // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  while (1) {
    // write code to test switches and LEDs
  }
}
// use main4 to test sound outputs
int main4(void) {
  uint32_t last = 0, now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init();          // initialize switches
  LED_Init();             // initialize LED
  Sound_Init();           // initialize sound
  TExaS_Init(ADC0, 6, 0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while (1) {
    // now = Switch_In(); // one of your buttons
    // if((last == 0)&&(now == 1)){
    //   Sound_Shoot(); // call one of your sounds
    // }
    // if((last == 0)&&(now == 2)){
    //   Sound_Killed(); // call one of your sounds
    // }
    // if((last == 0)&&(now == 4)){
    //   Sound_Explosion(); // call one of your sounds
    // }
    // if((last == 0)&&(now == 8)){
    //   Sound_Fastinvader1(); // call one of your sounds
    // }
    // // modify this to test all your sounds
  }
}
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main5(void) { // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_BLACK);
  Sensor.Init(); // PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0, 0, &TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
                                                   // initialize interrupts on
                                                   // TimerG12 at 30 Hz

  // initialize all data structures
  __enable_irq();

  while (1) {
    // wait for semaphore
    // clear semaphore
    // update ST7735R
    // check for end game or level switch
  }
}

// custom test
//  main6: test 12-bit DAC output on PA15
//  Scope PA15 to see ramp wave, or press buttons to test sounds
int main6(void) { // main6
  __disable_irq();
  PLL_Init(); // 80 MHz
  LaunchPad_Init();
  Sound_Init(); // inits DAC0/VREF, arms SysTick at 11kHz
  __enable_irq();

  // testing without interrupts, a quick sweep
  // Sweep 0 -> 4095 on PA15, visible on scope as sawtooth
  // for (uint32_t i = 0; i < 4096; i++) {
  //   DAC0->DATA0 = i;
  //   Clock_Delay1us(100); // 100us per step -> full ramp ~0.4s
  // }

  // sound array played via ISR
  // Press LaunchPad S1 (PA18) or S2 (PA14) to trigger sounds
  uint32_t last = 0, now;
  while (1) {
    now = LaunchPad_InS1() ? 1 : 0;
    if (last == 0 && now == 1) {
      Sound_EngineAccelerate();
    }
    last = now;
    Clock_Delay1ms(50);
  }
}

// main7: test StartScreen, potentiometer, and switches together
// Flow:
//   1. Runs StartScreen_Run() — exercises start screen display, pot-based
//   language
//      selection (arrow tracks pot position), SW1 to confirm, SW2 to reset.
//   2. After selection, shows a live diagnostic screen:
//        - Which language was chosen
//        - Live pot raw value (0-4095) and a 20-char ASCII bar
//        - Live state of SW1 and SW2 (PRESSED / ------)
//   3. Pressing SW2 on the diagnostic screen loops back to StartScreen_Run.
int main7(void) { // main7
  __disable_irq();
  PLL_Init();
  LaunchPad_Init();
  UART_Init();
  UART_OutString((char *)"[init] PLL+LaunchPad+UART done\r\n");

  __enable_irq(); // TIMG6 ISR must run to decrement Timer1/Timer2 inside
                  // disk_initialize
  DSTATUS dstat = disk_initialize(0);
  UART_OutString((char *)"[init] disk_initialize=");
  UART_OutUDec(dstat);
  UART_OutString((char *)"\r\n"); // 0=OK, non-zero=error

  ST7735_InitR(INITR_BLACKTAB);
  ST7735_InitPrintf();
  UART_OutString((char *)"[init] ST7735_InitPrintf done\r\n");

  ST7735_FillScreen(ST7735_BLACK);
  UART_OutString((char *)"[init] FillScreen done\r\n");

  Sensor.Init();
  Switch_Init();
  LED_Init();
  Sound_Init();
  UART_OutString((char *)"[init] all peripherals done\r\n");

  while (1) {
    UART_OutString((char *)"[loop] entering StartScreen_Run\r\n");
    // ---- Phase 1: Start screen (tests pot + switches + LCD) ----------------
    GameLanguage_t lang = StartScreen_Run(Sensor);
    UART_OutString((char *)"[loop] StartScreen_Run returned lang=");
    UART_OutUDec((uint32_t)lang);
    UART_OutString((char *)"\r\n");

    // ---- Phase 2: Live diagnostic screen -----------------------------------
    ST7735_FillScreen(ST7735_BLACK);

    ST7735_SetTextColor(ST7735_YELLOW);
    ST7735_SetCursor(1, 0);
    ST7735_OutString((char *)"=== DIAG SCREEN ===");

    // Show selected language (static, only drawn once)
    ST7735_SetTextColor(ST7735_CYAN);
    ST7735_SetCursor(0, 1);
    ST7735_OutString((char *)"Lang: ");
    if (lang == GAME_LANG_ENGLISH) {
      ST7735_OutString((char *)"English  ");
    } else {
      ST7735_OutString((char *)"Espanol  ");
    }

    ST7735_SetTextColor(ST7735_WHITE);
    ST7735_SetCursor(0, 3);
    ST7735_OutString((char *)"Pot raw (0-4095):");
    ST7735_SetCursor(0, 6);
    ST7735_OutString((char *)"Switches:");
    ST7735_SetTextColor(ST7735_RED);
    ST7735_SetCursor(0, 15);
    ST7735_OutString((char *)"SW2=Back to Menu");

    while (1) {
      Clock_Delay1ms(100);

      // --- Pot: raw value and ASCII bar ------------------------------------
      uint32_t raw = Sensor.In(); // 0-4095
      ST7735_SetTextColor(ST7735_WHITE);
      ST7735_SetCursor(0, 4);
      ST7735_OutUDec(raw);
      ST7735_OutString((char *)"    "); // clear leftover digits

      // 20-char bar: each char = 4096/20 = ~205 units
      uint32_t filled = raw / 205;
      if (filled > 20)
        filled = 20;
      ST7735_SetCursor(0, 5);
      ST7735_SetTextColor(ST7735_GREEN);
      ST7735_OutChar('[');
      for (uint32_t i = 0; i < 20; i++) {
        ST7735_OutChar(i < filled ? '#' : ' ');
      }
      ST7735_OutChar(']');

      // --- Switches: live state --------------------------------------------
      uint32_t sw = Switch_In(); // bit0=SW1(PA27), bit1=SW2(PA28)

      ST7735_SetCursor(0, 7);
      if (sw & 0x01) {
        ST7735_SetTextColor(ST7735_GREEN);
        ST7735_OutString((char *)"SW1(PA27): PRESSED");
      } else {
        ST7735_SetTextColor(ST7735_WHITE);
        ST7735_OutString((char *)"SW1(PA27): ------");
      }

      ST7735_SetCursor(0, 9);
      if (sw & 0x02) {
        ST7735_SetTextColor(ST7735_GREEN);
        ST7735_OutString((char *)"SW2(PA28): PRESSED");
      } else {
        ST7735_SetTextColor(ST7735_WHITE);
        ST7735_OutString((char *)"SW2(PA28): ------");
      }

      // SW2 rising edge -> return to start screen
      static uint32_t lastSw = 0;
      if (!(lastSw & 0x02) && (sw & 0x02)) {
        lastSw = sw;
        break;
      }
      lastSw = sw;
    }
    // outer while(1) -> StartScreen_Run again
  }
}

// main8: same init as main7, then after language select:
//   1. Loads each track tile from SD card, displays for 2 s.
//   2. Returns to the live diagnostic screen (SW2 -> back to menu).
int main8(void) {
  __disable_irq();
  PLL_Init();
  LaunchPad_Init();
  UART_Init();
  UART_OutString((char *)"[init] finished\r\n");

  __enable_irq();

  // SDImage_Init calls f_mount which calls disk_initialize internally — no separate call needed
  int sdrc = SDImage_Init();
  UART_OutString((char *)"[init] SDImage_Init=");
  UART_OutUDec((uint32_t)(sdrc < 0 ? (uint32_t)(-sdrc) : (uint32_t)sdrc));
  UART_OutString((char *)"\r\n");

  ST7735_InitR(INITR_BLACKTAB);
  ST7735_InitPrintf();
  ST7735_FillScreen(ST7735_BLACK);

  if (sdrc != 0) {
    ST7735_SetTextColor(ST7735_RED);
    ST7735_SetCursor(0, 0);
    ST7735_OutString((char *)"SD mount failed:");
    ST7735_OutUDec((uint32_t)sdrc);
    while (1) {}
  }

  Sensor.Init();
  Switch_Init();
  LED_Init();
  Sound_Init();

  static const char *tiles[] = {
      "T1_2.bin",     "T3_5.bin",   "T6_9.bin",   "T10_11.bin",
      "T11_BACK.bin", "T12_17.bin", "T17_20.bin",
  };
  static const int NUM_TILES = 7;

  UART_OutString((char *)"all init completed\r\n");

  while (1) {
    // ---- Phase 1: language select -----------------------------------------
    GameLanguage_t lang = StartScreen_Run(Sensor);

    // ---- Phase 2: slide-show of track tiles --------------------------------
    for (int i = 0; i < NUM_TILES; i++) {
      UART_OutString((char *)"[main8] drawing ");
      UART_OutString((char *)tiles[i]);
      UART_OutString((char *)"\r\n");

      int rc = SDImage_Draw(tiles[i], 0, 0);
      if (rc != 0) {
        ST7735_FillScreen(ST7735_BLACK);
        ST7735_SetTextColor(ST7735_RED);
        ST7735_SetCursor(0, 0);
        ST7735_OutString((char *)"Draw err:");
        ST7735_OutUDec((uint32_t)rc);
        ST7735_SetCursor(0, 1);
        ST7735_OutString((char *)tiles[i]);
      }
      Clock_Delay1ms(2000);
    }

    // ---- Phase 3: live diagnostic screen -----------------------------------
    ST7735_FillScreen(ST7735_BLACK);

    ST7735_SetTextColor(ST7735_YELLOW);
    ST7735_SetCursor(1, 0);
    ST7735_OutString((char *)"=== DIAG SCREEN ===");

    ST7735_SetTextColor(ST7735_CYAN);
    ST7735_SetCursor(0, 1);
    ST7735_OutString((char *)"Lang: ");
    if (lang == GAME_LANG_ENGLISH) {
      ST7735_OutString((char *)"English  ");
    } else {
      ST7735_OutString((char *)"Espanol  ");
    }

    ST7735_SetTextColor(ST7735_WHITE);
    ST7735_SetCursor(0, 3);
    ST7735_OutString((char *)"Pot raw (0-4095):");
    ST7735_SetCursor(0, 6);
    ST7735_OutString((char *)"Switches:");
    ST7735_SetTextColor(ST7735_RED);
    ST7735_SetCursor(0, 15);
    ST7735_OutString((char *)"SW2=Back to Menu");

    while (1) {
      Clock_Delay1ms(100);

      uint32_t raw = Sensor.In();
      ST7735_SetTextColor(ST7735_WHITE);
      ST7735_SetCursor(0, 4);
      ST7735_OutUDec(raw);
      ST7735_OutString((char *)"    ");

      uint32_t filled = raw / 205;
      if (filled > 20)
        filled = 20;
      ST7735_SetCursor(0, 5);
      ST7735_SetTextColor(ST7735_GREEN);
      ST7735_OutChar('[');
      for (uint32_t i = 0; i < 20; i++) {
        ST7735_OutChar(i < filled ? '#' : ' ');
      }
      ST7735_OutChar(']');

      uint32_t sw = Switch_In();

      ST7735_SetCursor(0, 7);
      if (sw & 0x01) {
        ST7735_SetTextColor(ST7735_GREEN);
        ST7735_OutString((char *)"SW1(PA27): PRESSED");
      } else {
        ST7735_SetTextColor(ST7735_WHITE);
        ST7735_OutString((char *)"SW1(PA27): ------");
      }

      ST7735_SetCursor(0, 9);
      if (sw & 0x02) {
        ST7735_SetTextColor(ST7735_GREEN);
        ST7735_OutString((char *)"SW2(PA28): PRESSED");
      } else {
        ST7735_SetTextColor(ST7735_WHITE);
        ST7735_OutString((char *)"SW2(PA28): ------");
      }

      static uint32_t lastSw8 = 0;
      if (!(lastSw8 & 0x02) && (sw & 0x02)) {
        lastSw8 = sw;
        break;
      }
      lastSw8 = sw;
    }
    // outer while(1) -> StartScreen_Run again
  }
}


static const char *images[] = {
    "T1_2.bin",
    "T3_5.bin",
    "T6_9.bin",
    "T10_11.bin",
    "T11_BACK.bin",   
    "T12_17.bin",
    "T17_20.bin",
};
static const int NUM_IMAGES = sizeof(images) / sizeof(images[0]);

//main 9 to test bare SD card mounting
int main9(void) {
    // extern "C" void __disable_irq(void);
    // extern "C" void __enable_irq(void);
    __disable_irq();

    Clock_Init80MHz(0);
    LaunchPad_Init();
    UART_Init();
    UART_OutString((char *)"[SDImageTest] starting\r\n");

    __enable_irq();
    disk_initialize(0);

    ST7735_InitPrintf();
    ST7735_FillScreen(ST7735_BLACK);

    int rc = SDImage_Init();
    UART_OutString((char *)"[SDImageTest] SDImage_Init=");
    UART_OutUDec((uint32_t)(rc < 0 ? (uint32_t)(-rc) : (uint32_t)rc));
    UART_OutString((char *)"\r\n");

    if (rc != 0) {
        ST7735_SetTextColor(ST7735_RED);
        ST7735_SetCursor(0, 0);
        ST7735_OutString((char *)"SD mount failed");
        while (1) {}
    }

    while (1) {
        for (int i = 0; i < NUM_IMAGES; i++) {
            UART_OutString((char *)"[SDImageTest] drawing ");
            UART_OutString((char *)images[i]);
            UART_OutString((char *)"\r\n");

            rc = SDImage_Draw(images[i], 0, 0);
            if (rc != 0) {
                ST7735_SetTextColor(ST7735_RED);
                ST7735_SetCursor(0, 0);
                ST7735_OutString((char *)"Draw err:");
                ST7735_OutUDec((uint32_t)rc);
            }
            Clock_Delay1ms(1000);
        }
    }
}
