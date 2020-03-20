#include "driver.h"


System Sys;
PID speedL_PID = {SPEED_KP, SPEED_KI, SPEED_KD, 100, 0, 0};
PID speedR_PID = {SPEED_KP, SPEED_KI, SPEED_KD, 100, 0, 0}; 
PID servMotor_PID = {SERV_MOTOR_KP, SERV_MOTOR_KI, SERV_MOTOR_KD, 0, 0, 0};

void get_speed(void)
{
    uint16 encoder_L, encoder_R;

    //读取计数值
    encoder_L = qtimer_quad_get(QTIMER_1, ENCODER_L_COUNT);
    encoder_R = qtimer_quad_get(QTIMER_2, ENCODER_R_COUNT);

    //计数清零
    qtimer_quad_clear(QTIMER_1, ENCODER_L_COUNT);
    qtimer_quad_clear(QTIMER_2, ENCODER_R_COUNT);

    //读取方向
    if(gpio_get(C1))    Sys.speed_L = encoder_L;
    else                Sys.speed_L = -encoder_L;
    if(gpio_get(C25))   Sys.speed_R = -encoder_R;
    else                Sys.speed_R = encoder_R;
}


int16 PIDcalc(PID *p, uint16 getPoint)
{
    int16 Error;
    int16 out;
    Error = p->setPoint - getPoint;
    if(Error < p->setPoint / 20)
        out = 0;
    else
        out = (p->Kp * (Error - p->pre_error)
            + p->Ki * Error
            + p->Kd * (Error - 2*p->pre_error + p->ppre_error)) / 10;   //除10避免浮点运算
    p->ppre_error = p->pre_error;
    p->pre_error = Error;
    return out;
}