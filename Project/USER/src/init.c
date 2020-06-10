#include "init.h"
#include "driver.h"
#include "config.h"


/**
 * @brief       系统初始化
 * @param       void
 * @return      void
 */
void init(void)
{
    //单片机外设初始化
    pit_init();

    /* 辅助调试模块初始化 */
#if OLED_ENABLE
    oled_init();
#endif
#if LCD_ENABLE
    lcd_init();
#endif
#if WIRELESS_ENABLE
    seekfree_wireless_init();
#endif

    //控制相关初始化
    mt9v03x_csi_init();
    encoder_init();
    motor_init();

    //中断优先级
    NVIC_SetPriority(CSI_IRQn, 1);
    NVIC_SetPriority(PIT_IRQn, 2);
}