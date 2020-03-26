#ifndef __INIT_H
#define __INIT_H

#include "headfile.h"

//宏定义舵机引脚
#define SERVE_MOTOR_PIN     PWM4_MODULE2_CHA_C30    //舵机信号引脚
#define S_MOTOR_MID_DUTY    3600                    //舵机居中占空比
#define S_MOTOR_MIN_DUTY    3900                    //车轮左打极限
#define S_MOTOR_MAX_DUTY    3300                    //车轮右打极限

//宏定义电机相关引脚
#define MOTOR_L_FORWARD     PWM2_MODULE3_CHA_D2     //左电机正转引脚
#define MOTOR_L_BACKWARD    PWM1_MODULE3_CHA_D0     //左电机反转引脚
#define MOTOR_R_FORWARD     PWM2_MODULE3_CHB_D3     //右电机正转引脚
#define MOTOR_R_BACKWARD    PWM1_MODULE3_CHB_D1     //右电机反转引脚
#define MOTOR_MAX_DUTY      10000                   //电机最高占空比

//宏定义编码器相关引脚
#define ENCODER_L_COUNT     QTIMER1_TIMER0_C0       //左编码器计数引脚
#define ENCODER_L_DIR       QTIMER1_TIMER1_C1       //左编码器方向引脚
#define ENCODER_R_COUNT     QTIMER2_TIMER0_C3       //右编码器计数引脚
#define ENCODER_R_DIR       QTIMER2_TIMER3_C25      //右编码器方向引脚

//宏定义辅助调试模块使能
#define OLED_ENABLE         0                       //OLED屏幕使能
#define LCD_ENABLE          1                       //1.8寸屏幕使能
#define WIRELESS_ENABLE     0                       //无线转串口模块使能

typedef struct System
{
    int16 speed_L;
    int16 speed_R;
    uint32 L_forward_duty;
    uint32 L_backward_duty;
    uint32 R_forward_duty;
    uint32 R_backward_duty;
    uint32 servMotor_duty;
}System;

typedef struct PID
{
    int16 Kp;
    int16 Ki;
    int16 Kd;
    int16 setPoint;
    int16 pre_error;
    int16 ppre_error;
}PID;

void init(void);

#endif