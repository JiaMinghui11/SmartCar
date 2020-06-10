#include "driver.h"
#include "config.h"

static void get_speed(void);
static int16 PIDcalc(PID_t *p, const int16 getPoint);

static System_t Sys;
static PID_t speedL_PID = {SPEED_KP, SPEED_KI, SPEED_KD, 150, 0, 0};
static PID_t speedR_PID = {SPEED_KP, SPEED_KI, SPEED_KD, 150, 0, 0}; 
static PID_t servMotor_PID = {SERV_MOTOR_KP, SERV_MOTOR_KI, SERV_MOTOR_KD, 0, 0, 0};


/**
 * @brief       编码器初始化
 * @param       void
 * @return      void
 */
void encoder_init(void)
{
    pit_interrupt_ms(ENCODER_CHANLE, ENCODER_PERIOD);

    /* 初始化计数引脚 */
    qtimer_quad_init(QTIMER_1, ENCODER_L_COUNT, ENCODER_L_DIR);
    qtimer_quad_init(QTIMER_2, ENCODER_R_COUNT, ENCODER_R_DIR);

    /* 初始化方向引脚 */
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
    pwm_init(S_MOTOR_PIN, S_MOTOR_FREQUENCY, S_MOTOR_MID_DUTY);

    //电机左
    pwm_init(MOTOR_L_FORWARD, MOTOR_FREQUENCY, 0);
    pwm_init(MOTOR_L_BACKWARD, MOTOR_FREQUENCY, 0);

    //电机右
    pwm_init(MOTOR_R_FORWARD, MOTOR_FREQUENCY, 0);
    pwm_init(MOTOR_R_BACKWARD, MOTOR_FREQUENCY, 0);

    Sys.L_forward_duty = 0;
    Sys.R_forward_duty = 0;
    Sys.L_backward_duty = 0;
    Sys.R_backward_duty = 0;
    Sys.servMotor_duty = S_MOTOR_MID_DUTY;
}


/**
 * @brief       编码器速度采集
 * @param       void
 * @return      void
 */
static void get_speed(void)
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
static int16 PIDcalc(PID_t *p, const int16 getPoint)
{
    int16 Error;
    int16 out;
    Error = p->setPoint - getPoint;

    out = (p->Kp * (Error - p->pre_error)
        + p->Ki * Error
        + p->Kd * (Error - 2*p->pre_error + p->ppre_error)) / 10;   //除10避免浮点运算

    p->ppre_error = p->pre_error;
    p->pre_error = Error;
    return out;
}


/**
 * @brief       舵机控制
 * @param       mid_line        中线数组
 * @return      void
 */
void servMoter_control(const int16 *mid_line)
{
    int16 error = 0;
    error = mid_line[105] - MT9V03X_CSI_W/2;

    int16 out = PIDcalc(&servMotor_PID, error);
    if(ABS(out) < S_MOTOR_THRE)     Sys.servMotor_duty += 0;
    else                            Sys.servMotor_duty += out;

    if(Sys.servMotor_duty > S_MOTOR_MAX_DUTY)   Sys.servMotor_duty = S_MOTOR_MAX_DUTY;
    if(Sys.servMotor_duty < S_MOTOR_MIN_DUTY)   Sys.servMotor_duty = S_MOTOR_MIN_DUTY;

    pwm_duty(S_MOTOR_PIN, Sys.servMotor_duty);
}


/**
 * @brief       电机控制
 * @param       void
 * @return      void      
 */
void speed_control(void)
{
    get_speed();

    Sys.L_forward_duty += PIDcalc(&speedL_PID, Sys.speed_L);
    Sys.R_forward_duty += PIDcalc(&speedR_PID, Sys.speed_R);

    if(Sys.L_forward_duty > MOTOR_MAX_DUTY)  Sys.L_forward_duty = MOTOR_MAX_DUTY;
    if(Sys.R_forward_duty > MOTOR_MAX_DUTY)  Sys.R_forward_duty = MOTOR_MAX_DUTY;

    pwm_duty(MOTOR_L_FORWARD, Sys.L_forward_duty);
    pwm_duty(MOTOR_R_FORWARD, Sys.R_forward_duty);
}