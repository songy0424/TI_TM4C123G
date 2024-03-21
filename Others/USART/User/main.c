/*
 * @Date: 2023-07-10 20:44:10
 * @LastEditTime: 2023-07-18 15:14:44
 * @Description: 串口通信
 */

#include "main.h"
#include "bsp_usart.h"

int main(void)
{
	// 配置时钟总线为40MHZ
	SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
	USART_Config();
	while (1)
	{
	}
}
