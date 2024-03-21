/*
 * @Date: 2023-07-19 16:47:02
 * @LastEditTime: 2023-07-19 22:08:50
 * @Description: IIC初始化
 */
#include "iic.h"

void InitI2C0()
{
	// enable i2c0 module
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

	// reset module
	SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

	// enable GPIO that contains I2C0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	// Configure the pin muxing for I2C0 functions on port B2 and B3.
	GPIOPinConfigure(GPIO_PB2_I2C0SCL);
	GPIOPinConfigure(GPIO_PB3_I2C0SDA);

	// Select the I2C function for these pins.
	GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
	GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

	I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

	// clear I2C FIFOs
	HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
}

void I2CSendSingleByte(uint8_t slave_addr, char data)
{
	// Tell the master module what address it will place on the bus when
	// communicating with the slave.
	I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

	// put the data to be sent in the FIFO
	I2CMasterDataPut(I2C0_BASE, data);

	// Initialize sending data from the MCU
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

	// wait while MCU is done transferring
	while (I2CMasterBusy(I2C0_BASE))
		;
}

void I2CSendDataBlock(uint8_t slave_addr, uint8_t *data, uint32_t num_bytes)
{
	uint8_t i;

	// 设置从设备地址
	I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

	// 开始发送数据块
	I2CMasterDataPut(I2C0_BASE, data[0]);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

	// 循环发送数据块的其他部分
	for (i = 1; i < num_bytes - 1; i++)
	{
		while (I2CMasterBusy(I2C0_BASE))
			;														 // 等待 I2C 主机变为空闲
		I2CMasterDataPut(I2C0_BASE, data[i]);						 // 将下一个字节放入数据寄存器
		I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); // 继续发送

		// Wait until MCU is done transferring.
	}

	// 发送最后一个字节并完成发送过程
	while (I2CMasterBusy(I2C0_BASE))
		;														   // 等待 I2C 主机变为空闲
	I2CMasterDataPut(I2C0_BASE, data[num_bytes - 1]);			   // 将最后一个字节放入数据寄存器
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH); // 完成发送过程
	while (I2CMasterBusy(I2C0_BASE))							   // 等待停止条件发送
		;
}
