/*
 * Switch.cpp
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
  // 0x00040081: GPIO input, input enable (bit 18), no internal pull
  // External pull-down resistors assumed; switch connects pin to 3.3V (positive logic)
  IOMUX->SECCFG.PINCM[PA28INDEX] = 0x00040081; // PA28: switch 2
  IOMUX->SECCFG.PINCM[PA27INDEX] = 0x00040081; // PA27: switch 1
}
// return current state of switches (positive logic: 1=pressed, 0=released)
// bit 0 = PA27 (switch 1), bit 1 = PA28 (switch 2)
//0 = both released, 1 = switch 1  (PA27) pressed, 2 = switch 2 (PA28) pressed, 3 = both pressed
uint32_t Switch_In(void){
  uint32_t data = GPIOA->DIN31_0;
  return (data >> 27) & 0x03;
}
