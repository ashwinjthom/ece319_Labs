// SDImageTest.cpp  —  standalone test for SDImage driver.
// Rename this function to main() (and rename the real main) to run the test.
// Cycles through all track tile images, each displayed for 1 second.
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../SDCFilecpp/diskio.h"
#include "../SDCFilecpp/ST7735_SDC.h"
#include "SDImage.h"
extern "C" {
#include "../inc/UART.h"
}

static const char *images[] = {
    "T1_2.bin",
    "T3_5.bin",
    "T6_9.bin",
    "T10_11.bin",
    "T11_BACK.bin",   // FAT 8.3: T11_BackStraight truncated to T11_BACK
    "T12_17.bin",
    "T17_20.bin",
};
static const int NUM_IMAGES = sizeof(images) / sizeof(images[0]);

int mainSDTest(void) {
    extern "C" void __disable_irq(void);
    extern "C" void __enable_irq(void);
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
