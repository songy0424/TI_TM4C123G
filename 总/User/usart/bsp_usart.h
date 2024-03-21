#ifndef __BSP_USART_H_
#define __BSP_USART_H_

#include "main.h"

void USART0_IRQHandler(void);
void USART1_IRQHandler(void);
void USART5_IRQHandler(void);

void Usart0_Init(void);
void Usart1_Init(void);
void Usart5_Init(void);

uint8_t usart5_sendData(uint8_t *data, uint16_t len);
uint16_t usart5_getRxData(uint8_t *buf, uint16_t len);
void UART_SendString(uint32_t ui32Base, const char *str);

#endif /*__BSP_USART_H_*/
