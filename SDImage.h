// SDImage.h
// Load and display RGB565 .bin images from SD card on the ST7735 LCD.
// Binary file format: 2-byte width + 2-byte height (little-endian uint16_t),
// followed by width*height uint16_t pixels in row-major order.
#ifndef SDIMAGE_H
#define SDIMAGE_H

#include <stdint.h>

// Mount the SD card filesystem. Call once after disk_initialize(0).
// Returns 0 on success, non-zero on failure.
int SDImage_Init(void);

// Draw a .bin image from the SD card at screen position (x, y).
// filename : 8.3 FAT name, e.g. "T1_2.bin"
// x, y     : top-left pixel on LCD
// Returns 0 on success, non-zero on error.
int SDImage_Draw(const char *filename, int16_t x, int16_t y);

#endif // SDIMAGE_H
