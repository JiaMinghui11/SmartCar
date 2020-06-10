#ifndef CONFIG_H
#define CONFIG_H

/* 宏定义PID相关 */
#define SPEED_KP            200                     //速度环 P
#define SPEED_KI            5                       //速度环 I
#define SPEED_KD            0                       //速度环 D
#define SERV_MOTOR_KP       150                     //转向环 P
#define SERV_MOTOR_KI       0                       //转向环 I
#define SERV_MOTOR_KD       300                     //转向环 D

/* 宏定义辅助调试模块使能 */
#define OLED_ENABLE         0                       //OLED屏幕使能
#define LCD_ENABLE          1                       //1.8寸屏幕使能
#define WIRELESS_ENABLE     0                       //无线转串口模块使能

/* 宏定义图像相关 */
#define IMAGE_W             MT9V03X_CSI_W           //图像宽度
#define IMAGE_H             MT9V03X_CSI_H           //图像高度

/* 宏定义舵机相关 */
#define S_MOTOR_THRE        10                      //舵机调整阈值
#define S_MOTOR_FREQUENCY   50                      //舵机信号频率，单位：Hz      
#define S_MOTOR_PIN         PWM4_MODULE2_CHA_C30    //舵机信号引脚
#define S_MOTOR_MID_DUTY    3600                    //舵机居中占空比
#define S_MOTOR_MAX_DUTY    3900                    //车轮左打极限
#define S_MOTOR_MIN_DUTY    3300                    //车轮右打极限

/* 宏定义电机相关 */
#define MOTOR_FREQUENCY     17000                   //电机信号频率，单位：Hz
#define MOTOR_L_FORWARD     PWM2_MODULE3_CHA_D2     //左电机正转引脚
#define MOTOR_L_BACKWARD    PWM1_MODULE3_CHA_D0     //左电机反转引脚
#define MOTOR_R_FORWARD     PWM2_MODULE3_CHB_D3     //右电机正转引脚
#define MOTOR_R_BACKWARD    PWM1_MODULE3_CHB_D1     //右电机反转引脚
#define MOTOR_MAX_DUTY      50000                   //电机最高占空比

/* 宏定义编码器相关 */
#define ENCODER_PERIOD      20                      //编码器采集周期，单位：ms
#define ENCODER_CHANLE      PIT_CH0                 //编码器采集定时通道
#define ENCODER_L_COUNT     QTIMER1_TIMER0_C0       //左编码器计数引脚
#define ENCODER_L_DIR       QTIMER1_TIMER1_C1       //左编码器方向引脚
#define ENCODER_R_COUNT     QTIMER2_TIMER0_C3       //右编码器计数引脚
#define ENCODER_R_DIR       QTIMER2_TIMER3_C25      //右编码器方向引脚

//#define ABS(X)              ((X) > 0) ? (X) : -(X)
//#define USE_OTUS            

#endif

