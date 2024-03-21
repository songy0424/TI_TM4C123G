/*
 * @Date: 2023-07-28 17:49:10
 * @LastEditTime: 2023-07-30 14:49:17
 * @Description: 按键中断配置
 * 可使用按键控制了
 */
#include "main.h"

bool key_flag = 0;

/**
 * @brief 按键初始化配置
 * @return
 */
void Key_Init(void)
{
	// 开启PROTF端口外设
	SysCtlPeripheralEnable(KeyPeripheral);

	// 配置PF4上拉输入
	GPIODirModeSet(KeyPort, KeyPin, GPIO_DIR_MODE_IN);
	GPIOPadConfigSet(KeyPort, KeyPin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); // 上拉

	// 配置中断触发类型
	GPIOIntTypeSet(KeyPort, KeyPin, GPIO_FALLING_EDGE); // 下降沿
	// 设置中断程序处理地址
	GPIOIntRegister(KeyPort, Key_IRQHandler);
	// 设置中断优先级

	IntPrioritySet(INT_GPIOF, 4);

	// 开启中断
	GPIOIntEnable(KeyPort, KeyIntFlags);
	IntEnable(KeyInterrupt);
	IntMasterEnable();
}

void Key_IRQHandler(void)
{
	uint32_t status = GPIOIntStatus(KeyPort, true);
	GPIOIntClear(KeyPort, status);

	if ((status & KeyPin) == KeyPin)
	{
		while (!GPIOPinRead(KeyPort, KeyPin))
			; // 等待按键松开
		key_flag = !key_flag;
	}
}
