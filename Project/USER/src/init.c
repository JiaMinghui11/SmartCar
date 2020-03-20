/**
 * @file        init.c
 * @brief       初始化相关函数
 * @version     查看version.txt
 */

#include "init.h"
#include "driver.h"

extern System Sys;

/**
 * @brief       编码器初始化
 * @param       void
 * @return      void
 */
void encoder_init(void)
{
    pit_interrupt_ms(PIT_CH0, 5);

    //初始化计数引脚
    qtimer_quad_init(QTIMER_1, ENCODER_L_COUNT, ENCODER_L_DIR);
    qtimer_quad_init(QTIMER_2, ENCODER_R_COUNT, ENCODER_R_DIR);

    //初始化方向引脚
    gpio_init(C1, GPI, 0, GPIO_PIN_CONFIG);
    gpio_init(C25, GPI, 0, GPIO_PIN_CONFIG);
}


/**
 * @brief       舵机 电机初始化
 * @param       void
 * @return      void
 */
void motor_init(void)
{
    //舵机归零
    pwm_init(SERVE_MOTOR_PIN, 50, S_MOTOR_MID_DUTY);

    //电机左
    pwm_init(MOTOR_L_FORWARD, 17000, 8000);
    pwm_init(MOTOR_L_BACKWARD, 17000, 0);

    //电机右
    pwm_init(MOTOR_R_FORWARD, 17000, 8000);
    pwm_init(MOTOR_R_BACKWARD, 17000, 0);

    Sys.L_forward_duty = 8000;
    Sys.R_forward_duty = 8000;
    Sys.L_backward_duty = 0;
    Sys.R_backward_duty = 0;
    Sys.servMotor_duty = S_MOTOR_MID_DUTY;
}


/**
 * @brief       系统初始化
 * @param       void
 * @return      void
 */
void init(void)
{
    //单片机外设初始化
    pit_init();

    //辅助调试模块初始化
    oled_init();

    //控制相关初始化
    encoder_init();
    motor_init();
}