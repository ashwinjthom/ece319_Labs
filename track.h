#ifndef TRACK_H
#define TRACK_H
#include <stdint.h>
#include "Car.h"
#include "../images/racingIMG.h"

struct TrackSegment {
    const char *image;
    int16_t boundary_x;   // pixel value where next segment starts
    int16_t boundary_y;
    int16_t entry_x;
    int16_t entry_y;
    int16_t cp_x;     // checkpoint center x
    int16_t cp_y;     // checkpoint center y
    int16_t cp_tol;   // pixel tolerance (radius)
    bool is_right;
    bool is_x;
    bool is_forward;
};

void Display_Segment(TrackSegment seg, Car &racecar, int16_t *old_x, int16_t *old_y);

void Update_Car(int16_t erase_x, int16_t erase_y,
                int16_t draw_x,  int16_t draw_y,
                const uint16_t *sprite, const char *filename);

void Display_Time(int16_t x, int16_t y, uint32_t counts);

#endif