#include "headfile.h"
#include "init.h"
#include "driver.h"

extern System Sys;
extern PID speedL_PID;

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