/*
 * @Date: 2023-07-29 21:43:38
 * @LastEditTime: 2023-07-29 22:08:16
 * @Description: 串口7初始化，用于OPENMV
 */
#include "bsp_openmv.h"

int x, y;

volatile static uint32_t rxBuffer[10];
volatile static uint32_t buffer_flag = 0;
/**
 * @brief 串口7初始化
 * @return
 */
void Usart7_Init(void)
{
	// 使能外设
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);

	// 使能复用
	GPIOPinConfigure(GPIO_PE0_U7RX);
	GPIOPinConfigure(GPIO_PE1_U7TX);

	// 分配信号
	GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_0);
	GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_1);

	// 配置串口7波特率与校验位，停止位，字长等
	UARTConfigSetExpClk(UART7_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

	// 使能串口的接收与接收超时中断
	UARTIntEnable(UART7_BASE, UART_INT_RX | UART_INT_RT);

	// 注册中断函数
	UARTIntRegister(UART7_BASE, USART7_IRQHandler);

	// 设置中断优先级，中断优先级有8个，0最高
	IntPrioritySet(INT_UART7, 4);

	// 开启中断
	IntEnable(INT_UART7);
	IntMasterEnable();

	// 使能串口
	UARTEnable(UART7_BASE);
}

/**
 * @brief 串口7中断函数
 * @return
 */
void USART7_IRQHandler(void)
{
	uint32_t status = UARTIntStatus(UART7_BASE, true);
	UARTIntClear(UART7_BASE, status);
	Openmv_Receive_Data();
}

/**
 * @brief OPENMV协议解析
 * @return 
 */
void Openmv_Receive_Data(void)
{
	volatile bool newDataAvailable = false;

	while (UARTCharsAvail(UART7_BASE))
	{
		uint32_t data = UARTCharGet(UART7_BASE);
		if (buffer_flag == 0 && data == 0x2C)
		{
			rxBuffer[buffer_flag++] = data;
		}
		else if (buffer_flag == 1 && data == 0x12)
		{
			rxBuffer[buffer_flag++] = data;
		}
		else if (buffer_flag >= 2 && data != 0x5B)
		{
			rxBuffer[buffer_flag++] = data;
		}
		else if (buffer_flag >= 4)
		{
			if (data == 0x5B)
			{
				rxBuffer[buffer_flag++] = data;

				x = rxBuffer[2];
				y = rxBuffer[3];
			}
			else if (data != 0x5B)
			{
				// 清空数组
				memset((void *)rxBuffer, 0, sizeof(rxBuffer));
			}
			buffer_flag = 0;
		}
		else
		{
			buffer_flag = 0;
			memset((void *)rxBuffer, 0, sizeof(rxBuffer));
		}
	}
}
