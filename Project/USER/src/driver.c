#include "driver.h"

extern int16 mid_line[MT9V03X_CSI_H];

System Sys;
PID speedL_PID = {SPEED_KP, SPEED_KI, SPEED_KD, 150, 0, 0};
PID speedR_PID = {SPEED_KP, SPEED_KI, SPEED_KD, 150, 0, 0}; 
PID servMotor_PID = {SERV_MOTOR_KP, SERV_MOTOR_KI, SERV_MOTOR_KD, 0, 0, 0};

/**
 * @brief       编码器速度采集
 * @param       void
 * @return      void
 */
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


/**
 * @brief       增量式PID计算
 * @param       p           PID结构体指针
 * @param       getPoint    PID控制器输入
 * @return      out         PID计算输出量
 */
int16 PIDcalc(PID *p, int16 getPoint)
{
    int16 Error;
    int16 out;
    Error = p->setPoint - getPoint;
    if(Error < p->setPoint / 20 && Error > -p->setPoint / 20)
        out = 0;
    else
        out = (p->Kp * (Error - p->pre_error)
            + p->Ki * Error
            + p->Kd * (Error - 2*p->pre_error + p->ppre_error)) / 10;   //除10避免浮点运算
    p->ppre_error = p->pre_error;
    p->pre_error = Error;
    return out;
}


/**
 * @brief       舵机控制
 * @param       void
 * @return      void
 */
void servMoter_control(void)
{
    int16 error = 0;
    error = mid_line[105] - MT9V03X_CSI_W/2;

    int16 out = PIDcalc(&servMotor_PID, error);
    if(out < 10 && out > -10)   Sys.servMotor_duty += 0;
    else                        Sys.servMotor_duty += out;

    if(Sys.servMotor_duty > 3900)   Sys.servMotor_duty = 3900;
    if(Sys.servMotor_duty < 3300)   Sys.servMotor_duty = 3300;
    pwm_duty(SERVE_MOTOR_PIN, Sys.servMotor_duty);
}