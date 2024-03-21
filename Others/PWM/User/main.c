/*
 * @Date: 2023-07-10 20:44:10
 * @LastEditTime: 2023-07-18 16:09:50
 * @Description: PWM输出
 */

#include "main.h"
#include "bsp_pwm.h"

float d = 0.01;
float duty = 0.1;
_Bool flag = 0;

int main(void)
{
    // 设置时钟总线是40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    // led初始化
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3, GPIO_DIR_MODE_OUT);

    // GPIO_STRENGTH_2MA每个引脚最大可承受2mA的电流,  GPIO_PIN_TYPE_STD表示引脚类型为标准引脚，即没有外部上下拉电阻
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    // pwm初始化
    PWM_Config();

    while (1)
    {
        duty += d;
        // 控制一个颜色的灯先亮后灭之后再换另一个颜色先亮后灭，依次往复
        if (duty > 0.9)
        {
            d = -0.01;
        }
        else if (duty < 0.1)
        {
            d = 0.01;
            flag = !flag;
        }
        if (flag == 0)
        {
            PWM_duty(PWM1_BASE, PWM_OUT_6, PWM_OUT_6_BIT, PWM_GEN_3, duty);
        }
        else
        {
            PWM_duty(PWM1_BASE, PWM_OUT_7, PWM_OUT_7_BIT, PWM_GEN_3, duty);
        }
        Delay_ms(10);
    }
}
