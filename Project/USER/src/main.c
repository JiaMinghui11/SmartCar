#include "headfile.h"
#include "init.h"
#include "driver.h"

extern System Sys;
extern PID speedL_PID;

int main(void)
{
    DisableGlobalIRQ();
    board_init();   //务必保留，本函数用于初始化MPU 时钟 调试串口
    systick_delay_ms(100);	//延时100ms，等待主板其他外设上电成功
    
    init();

    EnableGlobalIRQ(0);
    while(1)
    {  
        
    }    
}