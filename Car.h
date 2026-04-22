#ifndef CAR_H
#define CAR_H
#include <stdint.h>

typedef enum{MAZDA, LOTUS, PORSHE} Make;

class Car {
    Make model;
    int32_t v_fp;
    int32_t x_fp; // x position
    int32_t y_fp; // y position
    int32_t vx_fp; // x-axis velocity
    int32_t vy_fp; // y-axis velocity
    int32_t heading; // angle relative to display
    uint8_t gear;
    uint32_t rpm;
    const uint32_t *torque_fp; // determine acceleration based off power curve
    const uint16_t *image;

    void Update_Velocity(uint32_t data);
    void Set_Angle(uint32_t data);
    void shift();
    void calc_rpm(uint32_t data);

public:
    Car();
    void Set_Model(Make);
    void Reset(void);
    void Update_Position(uint32_t os, uint32_t o);
    int16_t Get_x(void);
    int16_t Get_y(void);
    int32_t Get_heading(void);
    void Set_Pos(uint32_t x, uint32_t y);
};

#endif