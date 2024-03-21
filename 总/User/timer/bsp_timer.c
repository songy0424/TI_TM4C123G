/*
 * @Date: 2023-07-10 20:44:10
 * @LastEditTime: 2023-07-31 21:08:30
 * @Description: 定时器配置
 */

#include "bsp_timer.h"

/**
 * @brief 定时器0的初始化
 * @return
 */
void Timer0_Init(void)
{
    // 使能定时器0时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC_UP);

    // 配置定时器0周期为1ms,只能这样设置，因为寄存器可能会超出范围
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / 1000 - 1);

    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0_IRQHandler);

    // 使能time0的定时器A为超时中断
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // 设置中断优先级
    IntPrioritySet(INT_TIMER0A, 0);

    // 使能中断
    IntEnable(INT_TIMER0A);

    // 启用处理器中断
    IntMasterEnable();

    // 使能定时器
    TimerEnable(TIMER0_BASE, TIMER_A);
}
