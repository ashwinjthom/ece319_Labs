#include "track.h"
#include "../inc/ST7735.h"
#include "../inc/Clock.h"

#define NUM_SEGMENTS 2

extern const TrackSegment track[NUM_SEGMENTS];
extern uint8_t track_idx;
extern const uint16_t *current_bg;
extern bool cleared;

void Select_Segment(TrackSegment seg, Car &racecar, int16_t *old_x, int16_t *old_y){
    bool crossed;
    int16_t x = *old_x;
    int16_t y = *old_y;

    if(x - seg.cp_x > 0) x -= seg.cp_x;
    else x = -(x-seg.cp_x);
    if(y - seg.cp_y > 0) x -= seg.cp_y;
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
        current_bg = track[track_idx].image;
        cleared = false;
        if(seg.is_x) {
        racecar.Set_Pos(seg.entry_x, *old_y);
        *old_x = seg.entry_x;
        } else { 
        racecar.Set_Pos(*old_x, seg.entry_y);
        *old_y = seg.entry_y;
        }
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