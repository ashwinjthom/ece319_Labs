#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include <stdint.h>
#include "../inc/SlidePot.h"

typedef enum {
  GAME_LANG_ENGLISH = 0,
  GAME_LANG_SPANISH = 1
} GameLanguage_t;

// Blocking start screen flow. Call after LCD, Switch, and Sensor.Init().
// Phase 1 — Splash: waits for SW1 rising edge to proceed.
// Phase 2 — Language select: pot steers arrow (> 2048 = Spanish),
//            SW1 rising edge confirms, SW2 rising edge resets to splash.
// Returns the selected language.
GameLanguage_t StartScreen_Run(SlidePot &pot);

#endif /* STARTSCREEN_H */
