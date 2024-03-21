/*
 * @Date: 2023-07-19 16:47:02
 * @LastEditTime: 2023-07-19 22:12:26
 * @Description: U8G2图形库配置
 */

#include "oled.h"
#include "i2c.h" //官方库
#include "iic.h"

/**
 * @brief U8G2 iic 回调函数配置
 * @param {u8x8_t} *u8x8
 * @param {uint8_t} msg
 * @param {uint8_t} arg_int
 * @param {void} *arg_ptr
 * @return
 */
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	static uint8_t buffer[128];
	static uint8_t buf_idx;
	uint8_t *data;

	switch (msg)
	{
	case U8X8_MSG_BYTE_INIT:
	{
		InitI2C0(); // I2C初始化
	}
	break;

	case U8X8_MSG_BYTE_START_TRANSFER:
		buf_idx = 0;
		break;

	case U8X8_MSG_BYTE_SEND:
		data = (uint8_t *)arg_ptr;
		while (arg_int > 0)
		{
			buffer[buf_idx++] = *data;
			data++;
			arg_int--;
		}
		break;

	case U8X8_MSG_BYTE_END_TRANSFER:
		I2CSendDataBlock(OLED_ADDRESS, buffer, buf_idx);
		break;

	case U8X8_MSG_BYTE_SET_DC:
		break;

	default:
		return 0;
	}
	return 1;
}

/**
 * @brief 延迟1us左右
 * @param {uint32_t} time 延时时间，单位us
 * @return
 */
void delay_us(uint32_t time)
{
	uint32_t i = 3180 * time;
	while (i--)
		;
}

/**
 * @brief U8G2 delay 回调函数配置
 * @param {u8x8_t} *u8x8
 * @param {uint8_t} msg
 * @param {uint8_t} arg_int
 * @param {void} *arg_ptr
 * @return
 */
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch (msg)
	{
	case U8X8_MSG_DELAY_100NANO: // delay arg_int * 100 nano seconds
		break;
	case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
		break;
	case U8X8_MSG_DELAY_MILLI: // delay arg_int * 1 milli second
		delay_us(arg_int);
		break;
	case U8X8_MSG_DELAY_I2C:	  // arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
		break;					  // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
	case U8X8_MSG_GPIO_I2C_CLOCK: // arg_int=0: Output low at I2C clock pin
		break;					  // arg_int=1: Input dir with pullup high for I2C clock pin
	case U8X8_MSG_GPIO_I2C_DATA:  // arg_int=0: Output low at I2C data pin
		break;
	case U8X8_MSG_GPIO_MENU_SELECT:
		u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
		break;
	case U8X8_MSG_GPIO_MENU_NEXT:
		u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
		break;
	case U8X8_MSG_GPIO_MENU_PREV:
		u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
		break;
	case U8X8_MSG_GPIO_MENU_HOME:
		u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
		break;
	default:
		u8x8_SetGPIOResult(u8x8, 1); // default return value
		break;
	}
	return 1;
}

/**
 * @brief U8G2初始化调用
 * @param {u8g2_t}
 * @return
 */
void u8g2Init(u8g2_t *u8g2)
{
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay); // 初始化 u8g2 结构体
	u8g2_InitDisplay(u8g2);																		  // 根据所选的芯片进行初始化工作，初始化完成后，显示器处于关闭状态
	u8g2_SetPowerSave(u8g2, 0);																	  // 打开显示器
	u8g2_ClearBuffer(u8g2);
}
