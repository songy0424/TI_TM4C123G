/*
 * @Date: 2023-07-17 19:20:50
 * @LastEditTime: 2023-07-18 14:20:51
 * @Description:PWM初始化
 */
#include "bsp_pwm.h"

void PWM_Config(void)
{
    // 因为设置了时钟总线是40MHz，所以在这里分一下频设置为4分频，那么PWM时钟就是10MHz
    SysCtlPWMClockSet(SYSCTL_PWMDIV_4); // 让总线时钟进行合理分频并作为PWM时钟

    // 使能GPIOF与PWM1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);

    // 为GPIOF_PIN_2与GPIOF_PIN_3分配PWM信号
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2); // 为引脚分配PWM信号
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);

    // 对GPIOF_PIN_2与GPIOF_PIN_3使能引脚复用
    GPIOPinConfigure(GPIO_PF2_M1PWM6); // 使能复用
    GPIOPinConfigure(GPIO_PF3_M1PWM7);

    // 设置PWM1模块的第四个发生器为向下计数与不同步计数
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC); // 配置PWM发生器

    // 设置PWM1模块的第四个发生器每个计数周期为1000个数，而PWM时钟为10MHz，那么PWM输出频率就是10 ^ 7 / 1000为10KHz，不能超过65535
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 1000); // 设置PWM输出频率

    // 设置PWM1模块的第六个通道的占空比为10%，这个函数的第三个参数为周期内的高电平数，所以可以通过PWMGenPeriodGet(获取PWM发生器模块的周期)得出一个周期内的计数总数再乘0.1然后减1就行
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) * 0.1 - 1); // 设置PWM输出占空比
    // 同理，只不过是设置第七个通道
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) * 0.1 - 1);

    // 使能第六个通道
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true); // 使能输出通道
    // 使能第七个通道
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true); // 使能发生器

    // 使能第三个发生器
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
}

// 自定义函数用来设置占空比
void PWM_duty(uint32_t ui32Base, uint32_t ui32PWMOut, uint32_t ui32PWMOutBits, uint32_t ui32Gen, float duty)
{
    PWMPulseWidthSet(ui32Base, ui32PWMOut, PWMGenPeriodGet(ui32Base, ui32Gen) * duty - 1);
}
