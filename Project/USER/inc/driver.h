#ifndef __DRIVER_H
#define __DRIVER_H

#include "headfile.h"
#include "init.h"

typedef struct System_t
{
    int16 speed_L;
    int16 speed_R;
    uint32 L_forward_duty;
    uint32 L_backward_duty;
    uint32 R_forward_duty;
    uint32 R_backward_duty;
    uint32 servMotor_duty;
}System_t;

typedef struct PID_t
{
    int16 Kp;
    int16 Ki;
    int16 Kd;
    int16 setPoint;
    int16 pre_error;
    int16 ppre_error;
}PID_t;

void encoder_init(void);
void motor_init(void);
void servMoter_control(const int16 *mid_line);
void speed_control(void);

#endif