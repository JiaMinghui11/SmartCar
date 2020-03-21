#ifndef __DRIVER_H
#define __DRIVER_H

#include "headfile.h"
#include "init.h"

//速度PID系数
#define SPEED_KP    100
#define SPEED_KI    10
#define SPEED_KD    0

//转向PID系数
#define SERV_MOTOR_KP   300
#define SERV_MOTOR_KI   0
#define SERV_MOTOR_KD   10

void get_speed(void);
int16 PIDcalc(PID *p, int16 getPoint);

#endif