// SDImage.cpp
#include "SDImage.h"
#include "../SDCFilecpp/ST7735_SDC.h"
#include "../SDCFilecpp/ff.h"
#include "../SDCFilecpp/diskio.h"
extern "C" {
#include "../inc/UART.h"
}

static FATFS g_fs;

int SDImage_Init(void) {
    // Step 1: initialize the physical SD card
    DSTATUS dstat = disk_initialize(0);
    UART_OutString((char *)"[SD] disk_initialize=");
    UART_OutUDec((uint32_t)dstat);
    UART_OutString((char *)"\r\n");
    UART_OutString((char *)"[SD] CardType=");
    UART_OutUDec((uint32_t)disk_get_cardtype());
    UART_OutString((char *)"\r\n");
    if (dstat) return -10;  // physical init failed

    // Step 2: test that a raw sector read actually works before f_mount
    uint8_t sect0[512];
    DRESULT dr = disk_read(0, sect0, 0, 1);
    UART_OutString((char *)"[SD] disk_read(0)=");
    UART_OutUDec((uint32_t)dr);
    UART_OutString((char *)" sig=0x");
    UART_OutUDec((uint32_t)sect0[510]);
    UART_OutString((char *)"/0x");
    UART_OutUDec((uint32_t)sect0[511]);
    UART_OutString((char *)"\r\n");
    if (dr != RES_OK) return -11;  // raw read failed

    // Step 3: mount filesystem
    FRESULT res = f_mount(&g_fs, "", 1);
    UART_OutString((char *)"[SD] f_mount=");
    UART_OutUDec((uint32_t)res);
    UART_OutString((char *)"\r\n");
    return (res == FR_OK) ? 0 : (int)res;
}

int SDImage_Draw(const char *filename, int16_t x, int16_t y) {
    FIL fil;
    FRESULT res = f_open(&fil, filename, FA_READ);
    if (res != FR_OK) return (int)res;

    // Read header: width, height (each 2 bytes, little-endian)
    uint16_t dims[2];
    UINT br;
    res = f_read(&fil, dims, sizeof(dims), &br);
    if (res != FR_OK || br != sizeof(dims)) { f_close(&fil); return -1; }

    int16_t w = (int16_t)dims[0];
    int16_t h = (int16_t)dims[1];

    // Line buffer: one row of up to 128 pixels = 256 bytes
    uint16_t linebuf[128];
    UINT row_bytes = (UINT)(w * 2);

    for (int16_t row = 0; row < h; row++) {
        res = f_read(&fil, linebuf, row_bytes, &br);
        if (res != FR_OK || br != row_bytes) { f_close(&fil); return -2; }
        ST7735_DrawBitmap(x, y + row, linebuf, w, 1);
    }

    f_close(&fil);
    return 0;
}
