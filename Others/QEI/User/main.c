/*
 * @Date: 2023-07-10 20:44:10
 * @LastEditTime: 2023-07-19 13:43:48
 * @Description: QEI编码器获取脉冲
 */

#include "main.h"
#include "bsp_qei.h"
#include "bsp_usart.h"

int main(void)
{
    // 系统时钟为40MHZ
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL);

    USART_Config();
    Init_QEI();
    Init_Timer();

    while (1)
    {
    }
}
