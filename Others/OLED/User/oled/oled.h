#ifndef __OLED_H__
#define __OLED_H__

#include "main.h"
#include "u8g2.h"

#define OLED_ADDRESS u8x8_GetI2CAddress(u8x8) >> 1 // OLED地址

uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
void delay_us(uint32_t time);
void u8g2Init(u8g2_t *u8g2);

#endif
