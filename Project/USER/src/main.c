#include "headfile.h"
#include "init.h"
#include "driver.h"
#include "camera.h"

extern System Sys;
extern PID speedL_PID;
extern uint8 threshold;
extern int16 mid_line[MT9V03X_CSI_H];

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
            OTUS(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H);
            image_scan();
            oled_dis_bmp(MT9V03X_CSI_H, MT9V03X_CSI_W, mt9v03x_csi_image[0], threshold);
            oled_show_line((uint8*)mid_line, MT9V03X_CSI_H);
            mt9v03x_csi_finish_flag = 0;
        }
    }    
}