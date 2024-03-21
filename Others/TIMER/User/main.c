/*
 * @Date: 2023-07-10 20:44:10
 * @LastEditTime: 2023-07-18 16:19:15
 * @Description: 定时器使用，1s闪烁led
 */

#include "main.h"
#include "bsp_timer.h"

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_XTAL_8MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_DIR_MODE_OUT);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
	
		Timer_Config();
    while (1)
    {
        if (flag == 0)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        }
    }
}
