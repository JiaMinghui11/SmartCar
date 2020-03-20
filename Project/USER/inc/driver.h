#ifndef __DRIVER_H
#define __DRIVER_H

#include "headfile.h"
#include "init.h"

//速度PID系数
#define SPEED_KP    20
#define SPEED_KI    1
#define SPEED_KD    0

//转向PID系数
#define SERV_MOTOR_KP   300
#define SERV_MOTOR_KI   0
#define SERV_MOTOR_KD   10

void get_speed(void);
int16 PIDcalc(PID *p, uint16 getPoint);

#endif