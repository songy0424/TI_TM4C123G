/*
 * @Date: 2023-07-29 12:32:38
 * @LastEditTime: 2023-07-29 21:43:14
 * @Description: 蜂鸣器配置
 */
#include "main.h"

/**
 * @brief 蜂鸣器初始化配置
 * @return
 */
void Beep_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // 将PF2配置为输出模式
    GPIOPinTypeGPIOOutput(BeepPort, BeepPin);
    GPIOPinWrite(BeepPort, BeepPin, ~BeepPin);
}

void Beep_Ring(int ms)
{
    GPIOPinWrite(BeepPort, BeepPin, BeepPin); // 打开蜂鸣器

    Delay_ms(ms); // 可以换成系统延时

    GPIOPinWrite(BeepPort, BeepPin, ~BeepPin); // 关闭蜂鸣器
}
