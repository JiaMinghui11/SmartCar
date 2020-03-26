#include "headfile.h"
#include "init.h"
#include "driver.h"
#include "camera.h"

extern System Sys;
extern PID speedL_PID;
extern PID servMotor_PID;
extern uint8 threshold;
extern int16 mid_line[MT9V03X_CSI_H];

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

int main(void)
{
    DisableGlobalIRQ();
    board_init();   //务必保留，本函数用于初始化MPU 时钟 调试串口
    systick_delay_ms(100);	//延时100ms，等待主板其他外设上电成功
    
    init();

    EnableGlobalIRQ(0);
    while(1)
    {  
        if(mt9v03x_csi_finish_flag)
        {
            lcd_displayimage032_zoom(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, MT9V03X_CSI_W, MT9V03X_CSI_H);
            find_line();
            servMoter_control();
            mt9v03x_csi_finish_flag = 0;
        }
    }    
}