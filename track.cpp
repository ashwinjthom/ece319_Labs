#include "track.h"
#include "../inc/ST7735.h"
#include "../inc/Clock.h"

#define NUM_SEGMENTS 2

extern const TrackSegment track[NUM_SEGMENTS];
extern uint8_t track_idx;
extern const uint16_t *current_bg;
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
        
        ST7735_DrawBitmap(0, 159, current_bg, 128, 160);  // redraw background
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

void Erase_Car(int16_t x, int16_t y, const uint16_t *background) {
    uint16_t patch[14 * 14];
    for (int row = 0; row < 14; row++) {
        for (int col = 0; col < 14; col++) {
            int src_row = (159 - y) + row;
            int src_col = x + col;
            if(src_row >= 0 && src_row < 160 && src_col >= 0 && src_col < 128)
                patch[row * 14 + col] = background[src_row * 128 + src_col];
        }
    }
    ST7735_DrawBitmap(x, y, patch, 14, 14);
}

void Display_Time(int16_t x, int16_t y, uint32_t counts){
    uint32_t sec = counts / 31; // time in seconds
    uint8_t min = sec / 60;
    sec = sec % 60;

    char time[] = {
    (char) (0x30 + min % 10), ':', 
    (char) (0x30 + sec / 10), (char) (0x30 + sec % 10)
    };
    ST7735_DrawString(x, y, time, 0xFFFF);
}

void Draw_Car(int16_t x, int16_t y, const uint16_t *sprite, const uint16_t *background) {
    uint16_t patch[14 * 14];
    for (int row = 0; row < 14; row++) {
        for (int col = 0; col < 14; col++) {
            uint16_t px = sprite[row * 14 + col];
            if (px == 0x0000) {
                int src_row = (159 - y) + row;
                int src_col = x + col;
                px = (src_row >= 0 && src_row < 160 && src_col >= 0 && src_col < 128)
                    ? background[src_row * 128 + src_col]
                    : 0x0000;
            }
            patch[row * 14 + col] = px;
        }
    }
    ST7735_DrawBitmap(x, y, patch, 14, 14);
}