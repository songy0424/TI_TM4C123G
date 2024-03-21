/*
 * @Date: 2023-07-18 14:37:09
 * @LastEditTime: 2023-07-30 18:16:39
 * @Description: 配置串口函数
 */
#include "bsp_usart.h"
#include "ringbuffer.h"

#define UART5_RX_BUFFER_SIZE 256
uint8_t uart5RxBuffer[UART5_RX_BUFFER_SIZE];
ringbuffer_t uart5RxFifo;

uint8_t dr;

/**
 * @brief 串口0初始化函数
 * 用于PID调试
 * @return
 */
void Usart0_Init(void)
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

    // 配置串口0波特率与校验位，停止位，字长等
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    // 使能串口的接收与接收超时中断
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    // 注册中断函数
    UARTIntRegister(UART0_BASE, USART0_IRQHandler);

    // 设置中断优先级，中断优先级有8个，0最高
    IntPrioritySet(INT_UART0, 7);

    // 开启中断
    IntEnable(INT_UART0);
    IntMasterEnable();

    // 使能串口
    UARTEnable(UART0_BASE);
}

/**
 * @brief 串口1初始化
 * 用于双车蓝牙通信
 * @return
 */
void Usart1_Init(void)
{
    // 使能外设
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    // 使能复用
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);

    // 分配信号
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_1);

    // 配置串口1波特率与校验位，停止位，字长等
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    // 使能串口的接收与接收超时中断
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

    // 注册中断函数
    UARTIntRegister(UART1_BASE, USART1_IRQHandler);

    // 设置中断优先级，中断优先级有8个，0最高
    IntPrioritySet(INT_UART1, 6);

    // 开启中断
    IntEnable(INT_UART1);
    IntMasterEnable();

    // 使能串口
    UARTEnable(UART1_BASE);
}

/**
 * @brief 串口5初始化函数
 * 用于获取IMU901数据
 * @return
 */
void Usart5_Init(void)
{
    // 使能外设
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);

    // 使能复用
    GPIOPinConfigure(GPIO_PE4_U5RX);
    GPIOPinConfigure(GPIO_PE5_U5TX);

    // 分配信号
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4);
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_5);

    // 配置串口0波特率与校验位，停止位，字长等
    UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    // 使能串口的接收与接收超时中断
    UARTIntEnable(UART5_BASE, UART_INT_RX | UART_INT_RT);

    // 注册中断函数
    UARTIntRegister(UART5_BASE, USART5_IRQHandler);

    // 设置中断优先级，中断优先级有8个，0最高
    IntPrioritySet(INT_UART5, 0);

    // 开启中断
    IntEnable(INT_UART5);
    IntMasterEnable();

    // 使能串口
    UARTEnable(UART5_BASE);

    // 初始化自定义FIFO缓冲区
    ringbuffer_init(&uart5RxFifo, uart5RxBuffer, UART5_RX_BUFFER_SIZE);
}

/**
 * @brief 串口0中断函数
 * PID上位机协议解析
 * @return
 */
void USART0_IRQHandler(void)
{
    uint32_t status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, status);

    dr = UARTCharGet(UART0_BASE);
    protocol_data_recv(&dr, 1);
}

/**
 * @brief 串口1中断函数
 * @return
 */
void USART1_IRQHandler(void)
{
    uint32_t status = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, status);
	
	   dr = UARTCharGet(UART1_BASE);
    protocol_data_recv(&dr, 1);
}

/**
 * @brief 串口5中断函数
 * IMU901上位机协议解析
 * @return
 */

void USART5_IRQHandler(void)
{
    uint32_t status = UARTIntStatus(UART5_BASE, true);
    UARTIntClear(UART5_BASE, status);

    uint8_t res = UARTCharGet(UART5_BASE);

    ringbuffer_in_check(&uart5RxFifo, (uint8_t *)&res, 1);
}

/**
 * @brief 发送字符串到串口
 * @param {uint32_t} ui32Base 串口
 * @param {char} *str 字符串
 * @return
 */
void UART_SendString(uint32_t ui32Base, const char *str)
{
    while (*str)
    {
        // 等待发送缓冲区为空
        while (UARTSpaceAvail(ui32Base) == false)
        {
        }
        // 发送一个字符
        UARTCharPut(ui32Base, *str++);
    }
}

/**
 * @brief 串口5发送数据
 * @param {uint8_t} *data 数据
 * @param {uint16_t} len 长度
 * @return {*}
 */
uint8_t usart5_sendData(uint8_t *data, uint16_t len)
{
    uint16_t i;
    for (i = 0; i < len; i++)
    {
        while (UARTBusy(UART5_BASE))
            ; // 等待 UART5 忙碌
        UARTCharPut(UART5_BASE, data[i]);
    }
    return 0; // 返回0表示正常状态
}

/**串口5接收数据
 * @brief
 * @param {uint8_t} *buf 数据区
 * @param {uint16_t} len 长度
 * @return {*}
 */
uint16_t usart5_getRxData(uint8_t *buf, uint16_t len)
{
    return ringbuffer_out(&uart5RxFifo, buf, len);
}
