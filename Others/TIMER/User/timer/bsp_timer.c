/*
 * @Date: 2023-07-10 20:44:10
 * @LastEditTime: 2023-07-18 16:31:08
 * @Description: 定时器配置
 */

#include "bsp_timer.h"

_Bool flag = 0;
void TIMER_IRQHandler(void);
void TIMER_WID_IRQHandler(void);

// 16/32bit定时器拆分
void Timer_Config(void)
{
    // 使能定时器TIMER0，16/32bit
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    /*
        TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC_UP表示配置定时器0为分组模式且通道A以周期上计时。
        分组模式是指定时器0被分成了两个独立的通道，对应通道A和通道B。通道A和通道B可以分别配置不同的工作模式和计时方式。
        周期上计时是指在计时值到达上限后，在重置计时器之前，计时器会自动重置，并产生一个周期性的中断。
        通过下面这行代码，可以配置定时器0为分组模式，通道A以周期上计时的方式工作，以适应不同的计时需求。
    */

    // 配置定时器，将定时器拆分，并配置拆分后的定时器A为周期性计数
    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC_UP);

    // 设置定时器A装载值，因为要1ms进一次中断，所以1ms=1/1000，所以重装载值为 SysCtlClockGet() / 1000 - 1
    // 假如为20ms，则重装载值为 SysCtlClockGet() / 50 - 1
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / 1000 - 1);

    // 为定时器A注册中断函数
    TimerIntRegister(TIMER0_BASE, TIMER_A, TIMER_IRQHandler);

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

void TIMER_IRQHandler(void)
{
    static uint32_t time_count = 0;

    // 读取定时器中断状态
    uint32_t status = TimerIntStatus(TIMER0_BASE, true);

    // 清除中断标志位
    TimerIntClear(TIMER0_BASE, status);

    // 1ms进一次中断
    time_count++;
    
    // 进一千次，也就是1s，翻转flag
    if (time_count == 1000)
    {
        time_count = 0;
        flag = !flag;
    }
}

// 32/64bit的定时器级联
void Timer_Wid_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);

    // 设置不拆分并且周期计数
    TimerConfigure(WTIMER0_BASE, TIMER_CFG_PERIODIC_UP);
    TimerLoadSet64(WTIMER0_BASE, SysCtlClockGet() / 1000 - 1);

    // 级联的情况下默认都是设置定时器A
    TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(WTIMER0_BASE, TIMER_A, TIMER_WID_IRQHandler);
    IntPrioritySet(INT_WTIMER0A, 1);
    IntEnable(INT_WTIMER0A);
    IntMasterEnable();
    TimerEnable(WTIMER0_BASE, TIMER_A);
}
void TIMER_WID_IRQHandler(void)
{
    static uint32_t time_count = 0;

    uint32_t status = TimerIntStatus(WTIMER0_BASE, true);
    TimerIntClear(WTIMER0_BASE, status);

    time_count++;
    if (time_count == 1000)
    {
        time_count = 0;
        flag = !flag;
    }
}
