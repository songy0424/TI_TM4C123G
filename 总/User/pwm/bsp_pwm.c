/*
 * @Date: 2023-07-17 19:20:50
 * @LastEditTime: 2023-07-29 13:08:19
 * @Description:PWM初始化
 */
#include "main.h"

/**
 * @brief PWM初始化配置
 * @return
 */
void Pwm_Init(void)
{
    // 因为设置了时钟总线是50MHz，所以在这里分一下频设置为2分频，那么PWM时钟就是25MHz
    SysCtlPWMClockSet(SYSCTL_PWMDIV_2); // 让总线时钟进行合理分频并作为PWM时钟

    // 使能GPIOF与PWM0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    // 为GPIOF_PIN_4与GPIOF_PIN_5分配PWM信号
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4); // 为引脚分配PWM信号
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);

    // 对GPIOF_PIN_4与GPIOF_PIN_5使能引脚复用
    GPIOPinConfigure(GPIO_PB4_M0PWM2); // 使能复用
    GPIOPinConfigure(GPIO_PB5_M0PWM3);

    // 设置PWM0模块的第一个发生器为向下计数与不同步计数
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC); // 配置PWM发生器

    // 设置PWM0模块的第一个发生器每个计数周期为1000个数，而PWM时钟为25MHz，那么PWM输出频率就是25 ^ 7 / 1000为25KHz，不能超过65535
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, 1000 - 1); // 设置PWM输出频率

    // 使能第0个和第1个通道
    // PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true); // 使能发生器，未使用，会在别的地方使能
    // PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, true);

    // 使能第一个发生器
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
}
