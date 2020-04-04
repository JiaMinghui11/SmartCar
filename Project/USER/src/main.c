#include "headfile.h"
#include "init.h"
#include "driver.h"
#include "camera.h"

extern System Sys;
extern PID speedL_PID;
extern PID servMotor_PID;
extern uint8 threshold;
extern int16 mid_line[MT9V03X_CSI_H];


int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    systick_delay_ms(100);	//��ʱ100ms���ȴ��������������ϵ�ɹ�
    
    init();

    EnableGlobalIRQ(0);
    while(1)
    {  
        
    }    
}