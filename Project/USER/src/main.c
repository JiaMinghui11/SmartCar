#include "headfile.h"
#include "init.h"
#include "driver.h"
#include "camera.h"
#include "config.h"

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
            direct_control();
        #if LCD_ENABLE
            lcd_displayimage032_zoom(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, MT9V03X_CSI_W, MT9V03X_CSI_H);
        #endif
            mt9v03x_csi_finish_flag = 0;
        }
    }    
}