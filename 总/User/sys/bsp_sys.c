/*
 * @Date: 2023-07-10 20:44:10
 * @LastEditTime: 2023-07-31 21:14:59
 * @Description: 系统滴答定时器配置
 * 在使用延时函数时尽量使用系统定时器的中断计数，这样可以保证cpu浪费时间较少
 */
#include "main.h"

extern uint16_t System_Time_ms;
extern uint16_t Send_Time;
extern uint16_t ShowOLED_Time;

/**
 * @brief 系统定时器初始化
 * @return
 */
void SysTick_Init(void)
{
    SysTickPeriodSet(SysCtlClockGet() / 1000); // 1ms进入一次中断
    SysTickIntRegister(SysTick_IRQHandler);
    SysTickIntEnable(); // 使能中断，打开定时器
    SysTickEnable();    // 可以在使用的时候调用 SysTickDisable(); 关闭定时器
}

/**
 * @brief 使用系统定时器的延时函数
 * @param {int} count 单位ms
 * @return
 */
void Delay_ms(int count)
{
    for (int i = 0; i < count; i++)
        SysCtlDelay(SysCtlClockGet() / 3000);
}

/**
 * @brief 系统定时器中断函数
 * @return
 */
void SysTick_IRQHandler(void)
{
    Send_Time++;
    ShowOLED_Time++;
    System_Time_ms++;
    if (System_Time_ms >= 500)
        System_Time_ms = 0;
}
