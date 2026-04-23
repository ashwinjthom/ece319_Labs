#include "track.h"
#include "../inc/Clock.h"
#include "SDImage.h"
#include "../SDCFilecpp/ff.h"
#include "../SDCFilecpp/diskio.h"
#include "../SDCFilecpp/ST7735_SDC.h"

#define NUM_SEGMENTS 2

extern const TrackSegment track[NUM_SEGMENTS];
extern uint8_t track_idx;
extern const char *current_bg;
extern bool cleared;
extern uint32_t count;
extern bool lap_complete;
extern uint32_t lap_record;
extern uint32_t lap_count;

void Display_Segment(TrackSegment seg, Car &racecar, int16_t *old_x, int16_t *old_y){
    bool crossed;
    int16_t x = *old_x;
    int16_t y = *old_y;

    if(x - seg.cp_x > 0) x -= seg.cp_x;
    else x = -(x-seg.cp_x);
    if(y - seg.cp_y > 0) y -= seg.cp_y;
    else y = -(y-seg.cp_y);
    
    // check if car is inside the checkpoint box
    if(!cleared) {
        if(x <= seg.cp_tol && y <= seg.cp_tol)
            cleared = true;
    }

    if(!cleared) return;   // boundary not live yet

    if(!seg.is_x) {
        if(seg.is_right) crossed = *old_x >= seg.boundary_x && *old_y <= seg.boundary_y;
        else crossed = *old_x <= seg.boundary_x && *old_y <=seg.boundary_y;
    } else {
        if(seg.is_right) crossed = *old_x <= seg.boundary_x && *old_y <= seg.boundary_y;
        else crossed = *old_x <= seg.boundary_x && *old_y >= seg.boundary_y;
    }
    
    if(crossed) {
        track_idx = (track_idx + 1) % NUM_SEGMENTS;
        if(track_idx == NUM_SEGMENTS - 1) lap_complete = true;
        current_bg = track[track_idx].image;
        cleared = false;

        if(seg.is_x) {
        racecar.Set_Pos(seg.entry_x, *old_y);
        *old_x = seg.entry_x;
        } else { 
        racecar.Set_Pos(*old_x, seg.entry_y);
        *old_y = seg.entry_y;
        }
        
        SDImage_Draw(current_bg, 0, 159);  // redraw background
        Display_Time(17, 0, count); // redraw lap time
        ST7735_SetCursor(0, 15);
        ST7735_OutUDec(lap_count); // redraw lap count
    }

    // display lap record if lap completed
    if(lap_complete && track_idx == 0 && *old_x >= 70 && y <= 100) {
        lap_count++;
        ST7735_SetCursor(0, 15);
        ST7735_OutUDec(lap_count);
        if (count < lap_record || lap_record == 0) {
            lap_record = count;
        }
        Display_Time(17, 15, lap_record); // draw lap record
        count = 0;
        lap_complete = false;
    } else if (crossed && lap_count != 0) {
        Display_Time(17, 15, lap_record); // redraw lap record
    }
}

void Update_Car(int16_t erase_x, int16_t erase_y,
                int16_t draw_x,  int16_t draw_y,
                const uint16_t *sprite, const char *filename) {
    FIL fil;
    UINT br;
    uint16_t erase_patch[14 * 14] = {};
    uint16_t draw_bg[14 * 14]     = {};

    if (f_open(&fil, filename, FA_READ) == FR_OK) {
        for (int row = 0; row < 14; row++) {
            DWORD off = 4 + ((DWORD)((159 - erase_y) + row) * 128 + erase_x) * 2;
            f_lseek(&fil, off);
            f_read(&fil, erase_patch + row * 14, 28, &br);
        }
        for (int row = 0; row < 14; row++) {
            DWORD off = 4 + ((DWORD)((159 - draw_y) + row) * 128 + draw_x) * 2;
            f_lseek(&fil, off);
            f_read(&fil, draw_bg + row * 14, 28, &br);
        }
        f_close(&fil);
    }

    uint16_t draw_patch[14 * 14];
    for (int i = 0; i < 14 * 14; i++)
        draw_patch[i] = (sprite[i] == 0x0000) ? draw_bg[i] : sprite[i];

    // All SD reads done — back-to-back LCD writes minimise the flicker window
    ST7735_DrawBitmap(erase_x, erase_y, erase_patch, 14, 14);
    ST7735_DrawBitmap(draw_x,  draw_y,  draw_patch,  14, 14);
}

void Display_Time(int16_t x, int16_t y, uint32_t counts){
    uint32_t sec = counts / 31; // time in seconds (ISR runs at 30 Hz)
    uint8_t min = sec / 60;
    sec = sec % 60;

    char time[] = {
    (char) (0x30 + min % 10), ':', 
    (char) (0x30 + sec / 10), (char) (0x30 + sec % 10)
    };
    ST7735_DrawString(x, y, time, 0xFFFF);
}

