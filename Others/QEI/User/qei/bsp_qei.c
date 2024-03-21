/*
 * @Date: 2023-07-18 19:21:54
 * @LastEditTime: 2023-07-19 14:03:53
 * @Description: QEI配置，可以获取编码器值
 */

#include "bsp_qei.h"
#include "bsp_usart.h"

#define TIMER_FREQUENCY 		50      // 定时器频率，单位为Hz
#define QEI_PULSES_PER_REV 	1320 		// 编码器每转的脉冲数

uint32_t pulse_count = 0;

/**
 * @brief 定时器0中断，为pid和编码器控制主程序
 * @return {*}
 */
void Timer0IntHandler(void)
{
    // 清除定时器中断标志
    uint32_t status = TimerIntStatus(TIMER0_BASE, true);

    // 清除中断标志位
    TimerIntClear(TIMER0_BASE, status);

    // 读取编码器脉冲数
    pulse_count = QEIPositionGet(QEI1_BASE);

    QEIPositionSet(QEI1_BASE, 0);

    // 计算编码器转速
    // uint32_t speed = pulse_count  * (TIMER_FREQUENCY * 60) / (QEI_PULSES_PER_REV);

    UART_SendNumber(pulse_count);
}

/**
 * @brief 定时器0的初始化
 * @return {*}
 */
void Init_Timer(void)
{
    // 使能定时器0和GPIOF模块时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC_UP);

    // 配置定时器0周期
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / 5 - 1);

    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);

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

/**
 * @brief QEI初始化，可以获取编码器值
 * @return {*}
 */
void Init_QEI(void)
{
    // 使能QEI相关GPIO引脚
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    // 使能QEI模块时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);

    // 配置QEI模块
    QEIConfigure(QEI1_BASE, QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP, 1320);

    // 配置GPIO引脚为QEI功能
    GPIOPinConfigure(GPIO_PC5_PHA1);
    GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinConfigure(GPIO_PC6_PHB1);
    GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_6);

    // 配置GPIO引脚的电气特性
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);

    // 使能QEI模块
    QEIEnable(QEI1_BASE);

    // 配置QEI模块的位置计数初始值
    QEIPositionSet(QEI1_BASE, 0);
}
