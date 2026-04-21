#include "../inc/Car.h"
#include "../inc/tables.h"
#include "images/racingIMG.h"
#include "../inc/ST7735.h"

#define MAX_STEERING_ANGLE 36
#define DRAG_COEFF 390//(390) //fixed point rr 1/s
#define ROLLING_RESISTANCE 1
#define DT 137
#define MASS 900
#define RPM_REDLINE     8500
#define RPM_UPSHIFT     8300   // base upshift point
#define RPM_DOWNSHIFT   3500   // base downshift point
#define WHEELBASE (2355 >> 6)   // = 36

#define pi 804
#define FP 12

#define X_MIN_FP (0 << FP)
#define X_MAX_FP (114 << FP)

#define Y_MIN_FP (13 << FP)
#define Y_MAX_FP (159 << FP)

//car images
const uint16_t *images[3] = {
    BlueBall, BlueBall, BlueBall
};

Car::Car(){
    model = LOTUS;
    v_fp = 0;
    x_fp = 57<<FP;
    y_fp = 128<<FP;
    vx_fp = 0;
    vy_fp = 0;
    heading = 300<<FP;
    gear = 1;
    torque_fp = lotus;
    image = images[LOTUS];
}

void Car::Reset(void) {
    x_fp = 57<<FP;
    y_fp = 128<<FP;
    v_fp = 0;
    vx_fp = 0;
    vy_fp = 0;
    gear = 1;
    heading = 300<<FP;
}

void Car::shift() {
    // UPSHIFT
    if (rpm > (RPM_UPSHIFT) && gear < 6) {
        gear++;
    }

    // DOWNSHIFT
    else if (rpm < (RPM_DOWNSHIFT) && gear > 1) {
        gear--;
    }
}

void Car::calc_rpm(uint32_t data) {
    data = (data * 6) >> 11;
    int32_t speed = (v_fp < 0) ? -v_fp : v_fp;
    uint32_t speed_i = (speed >> FP) % 8;

    if(gear == 1) rpm = exige_gear1[data][speed_i];
    else if(gear == 2) rpm = exige_gear2[data][speed_i];
    else if(gear == 3) rpm = exige_gear3[data][speed_i];
    else if(gear == 4) rpm = exige_gear4[data][speed_i];
    else if(gear == 5) rpm = exige_gear5[data][speed_i];
    else rpm = exige_gear6[data][speed_i];

    shift();

    if(gear == 1) rpm = exige_gear1[data][speed_i];
    else if(gear == 2) rpm = exige_gear2[data][speed_i];
    else if(gear == 3) rpm = exige_gear3[data][speed_i];
    else if(gear == 4) rpm = exige_gear4[data][speed_i];
    else if(gear == 5) rpm = exige_gear5[data][speed_i];
    else rpm = exige_gear6[data][speed_i];
}

void Car::Update_Velocity(uint32_t data) {
    int32_t in = data - 2048;

    if(in < 0) {
        if(v_fp == 0) return;
        in = -in;
        int32_t brake_scale = 4096 - ((in * 295) >> 11);
        v_fp = (v_fp * brake_scale) >> FP;
    } else {
        calc_rpm(in);
        uint32_t index = (rpm - 1000) * 100 / (8500 - 1000);
        if(index > 99) index = 99;
        int32_t a = (torque_fp[index] << 4) / MASS;

        int32_t rr = ((DRAG_COEFF * v_fp) >> FP) + ROLLING_RESISTANCE;
        if(v_fp > 0) rr = -rr;

        v_fp += ((a + rr) * DT) >> FP;
        if(v_fp < 0) v_fp = 0;
    }

    int32_t hsin = sin_table[((heading >> FP) + 90) % 360];
    int32_t hcos = sin_table[((heading >> FP) + 180) % 360];
    vx_fp = (int32_t)(((int64_t)hcos * v_fp) >> 8);
    vy_fp = (int32_t)(((int64_t)hsin * v_fp) >> 8);
}

void Car::Set_Angle(uint32_t data) {
    uint32_t remapped;
    if(data < 2300) remapped = (data * 2048) / 2300;
    else if(data > 3200)  remapped = 2048 + ((data - 3100) * 2047) / (4095 - 3100);
    else return;
    remapped = (remapped * 72) >> 12;
    int32_t steering_angle = ((int32_t)remapped - 36) << FP;

    if(v_fp < 64) return;

    int32_t dheading = (int32_t)(((int64_t)steering_angle * v_fp) / (((int64_t)WHEELBASE << (FP-2))));
    heading += dheading;
    heading = ((heading % (360 << FP)) + (360 << FP)) % (360 << FP);
}

void Car::Update_Position(uint32_t os, uint32_t o){
    Set_Angle(os);
    Update_Velocity(o);

    x_fp += vx_fp;
    y_fp += vy_fp;

    if(x_fp > X_MAX_FP) {x_fp = X_MAX_FP - 10; v_fp = 0; vx_fp = 0; vy_fp = 0;}
    else if(x_fp < X_MIN_FP) {x_fp = X_MIN_FP + 10; v_fp = 0; vx_fp = 0; vy_fp = 0;}

    if(y_fp > Y_MAX_FP) {y_fp = Y_MAX_FP - 10; v_fp = 0; vx_fp = 0; vy_fp = 0;}
    else if(y_fp < Y_MIN_FP) {y_fp = Y_MIN_FP + 10; v_fp = 0; vx_fp = 0; vy_fp = 0;}
}

int16_t Car::Get_x() {
    return x_fp >> FP;
}

int16_t Car::Get_y() {
    return y_fp >> FP;
}

int32_t Car::Get_heading(void) {
    return heading >> FP;
}

void Car::Draw_Car(int16_t x, int16_t y, const uint16_t *sprite, const uint16_t *background) {
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

void Car::Set_Pos(uint32_t x, uint32_t y) {
    x_fp = x << FP;
    y_fp = y << FP;
}