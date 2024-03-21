/*
 * @Date: 2023-07-18 14:37:09
 * @LastEditTime: 2023-07-18 15:35:01
 * @Description: 配置串口函数
 */
#include "bsp_usart.h"

void USART0_IRQHandler(void);

/**
 * @brief 串口初始化函数
 * @return {*}
 */
void USART_Config(void)
{
    // 使能外设
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // 使能复用
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    // 分配信号
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1);

    /*搭配UARTprintf使用*/
    // 设置串口0的时钟为UART_CLOCK_PIOSC
    //	UARTClockSourceSet( UART0_BASE,  UART_CLOCK_PIOSC);
    // 设置串口0波特率与波特时钟
    //	UARTStdioConfig(0, 115200, 16000000);
    /*与UARTCharPut，UARTCharPutNonBlocking等搭配使用*/

    // 配置串口0波特率与校验位，停止位，字长等
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    // 使能FIFO
    UARTFIFOEnable(UART0_BASE);

    /*
        FIFO的数据深度有1/8，1/4，1/2，3/4，7/8五种
        比如，设置接收FIFIO深度为1/8，那么就是FIFO中装入了16*1/8=2字节时触发中断
        如果不用FIFO，那么每接收一个字节都要触发一次中断，导致频繁的进入中断
    */

    // 接收发送的FIFO都为1/4，也就是16*1/4=4个字节
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX2_8, UART_FIFO_RX2_8);

    // 使能串口的接收与接收超时中断
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    // 注册中断函数
    UARTIntRegister(UART0_BASE, USART0_IRQHandler);

    // 设置中断优先级，中断优先级有8个，0最高
    IntPrioritySet(INT_UART0, 0);

    // 开启中断
    IntEnable(INT_UART0);
    IntMasterEnable();

    // 使能串口
    UARTEnable(UART0_BASE);
}

/**
 * @brief 串口中断函数，用于输入输出控制
 * @return {*}
 */
void USART0_IRQHandler(void)
{
    uint32_t re_buf;

    // 读取中断状态
    uint32_t status = UARTIntStatus(UART0_BASE, true);

    // 清除中断标志位
    UARTIntClear(UART0_BASE, status);

    // 判断UART0有没有字符未读取
    while (UARTCharsAvail(UART0_BASE))
    {
        // 如果有字符为读取就取出，使用UARTCharGetNonBlocking防止等待
        re_buf = UARTCharGetNonBlocking(UART0_BASE);
        // 将读取出的字符再发送
        UARTCharPutNonBlocking(UART0_BASE, re_buf); // 向指定端口发送字符。
    }
}
