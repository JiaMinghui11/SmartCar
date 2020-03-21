#include "headfile.h"
#include "init.h"
#include "driver.h"
#include "camera.h"

extern System Sys;
extern PID speedL_PID;
extern uint8 threshold;

int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    systick_delay_ms(100);	//��ʱ100ms���ȴ��������������ϵ�ɹ�
    
    init();

    EnableGlobalIRQ(0);
    while(1)
    {  
        if(mt9v03x_csi_finish_flag)
        {
            oled_dis_bmp(MT9V03X_CSI_H, MT9V03X_CSI_W, mt9v03x_csi_image[0], threshold);
            mt9v03x_csi_finish_flag = 0;
        }
    }    
}