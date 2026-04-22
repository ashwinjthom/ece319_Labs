// SDTest.cpp — bare-bones SD card test, no SDImage driver
// Tests: disk_initialize -> disk_read sector 0 -> f_mount -> f_opendir -> f_open
// Output: UART + ST7735 display

#include <stdint.h>
#include <stdio.h>
#include <ti/devices/msp/msp.h>

#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
extern "C" {
#include "../inc/UART.h"
}
#include "../SDCFilecpp/ST7735_SDC.h"
#include "../SDCFilecpp/diskio.h"
#include "../SDCFilecpp/ff.h"

void PLL_Init(void) { Clock_Init80MHz(0); }

// print a line to both UART and LCD (row advances automatically)
static int lcd_row = 0;
static void print(const char *msg, uint32_t val, int show_val) {
    UART_OutString((char *)msg);
    if (show_val) UART_OutUDec(val);
    UART_OutString((char *)"\r\n");

    ST7735_SetCursor(0, lcd_row);
    ST7735_OutString((char *)msg);
    if (show_val) ST7735_OutUDec(val);
    lcd_row++;
    if (lcd_row > 15) lcd_row = 0;
}

static FATFS g_fs;

int mainSDTest(void) {
    __disable_irq();
    PLL_Init();
    LaunchPad_Init();
    UART_Init();

    __enable_irq(); // disk_initialize needs timer ISR

    ST7735_InitR(INITR_BLACKTAB);
    ST7735_InitPrintf();
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_SetTextColor(ST7735_WHITE);

    print("=== SD RAW TEST ===", 0, 0);

    // Step 1: physical init
    DSTATUS dstat = disk_initialize(0);
    print("disk_init=", dstat, 1);
    print("CardType=",  disk_get_cardtype(), 1);
    if (dstat) {
        print("FAIL: no card?", 0, 0);
        while (1) {}
    }

    // Step 2: raw sector 0 read — check MBR signature 0x55 0xAA
    static uint8_t sect0[512];
    DRESULT dr = disk_read(0, sect0, 0, 1);
    print("disk_read=", dr, 1);
    print("sig[510]=0x", sect0[510], 1);
    print("sig[511]=0x", sect0[511], 1);
    if (dr != RES_OK) {
        print("FAIL: raw read", 0, 0);
        while (1) {}
    }
    if (sect0[510] != 0x55 || sect0[511] != 0xAA) {
        print("WARN:bad MBR sig", 0, 0);
    } else {
        print("MBR sig OK", 0, 0);
    }

    // Step 3: mount filesystem
    FRESULT fr = f_mount(&g_fs, "", 1);
    print("f_mount=", fr, 1);
    if (fr != FR_OK) {
        print("FAIL: mount", 0, 0);
        while (1) {}
    }

    // Step 4: list root directory
    DIR dir;
    FILINFO fno;
    fr = f_opendir(&dir, "/");
    print("f_opendir=", fr, 1);
    if (fr == FR_OK) {
        int count = 0;
        while (1) {
            fr = f_readdir(&dir, &fno);
            if (fr != FR_OK || fno.fname[0] == 0) break;
            UART_OutString((char *)"  ");
            UART_OutString(fno.fname);
            UART_OutString((char *)"\r\n");
            ST7735_SetCursor(0, lcd_row);
            ST7735_OutString(fno.fname);
            lcd_row++;
            if (lcd_row > 15) lcd_row = 0;
            count++;
        }
        f_closedir(&dir);
        print("files found=", count, 1);
    }

    // Step 5: try opening first expected tile
    FIL fil;
    fr = f_open(&fil, "T1_2.bin", FA_READ);
    print("open T1_2.bin=", fr, 1);
    if (fr == FR_OK) {
        uint8_t hdr[4];
        UINT br;
        f_read(&fil, hdr, 4, &br);
        print("hdr br=", br, 1);
        print("w=", hdr[0] | (hdr[1] << 8), 1);
        print("h=", hdr[2] | (hdr[3] << 8), 1);
        f_close(&fil);
    }

    print("=== DONE ===", 0, 0);
    while (1) {}
}
