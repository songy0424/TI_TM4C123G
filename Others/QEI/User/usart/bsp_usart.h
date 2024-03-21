#ifndef __BSP_USART_H_
#define __BSP_USART_H_

#include "main.h"

void USART_Config(void);
void USART0_IRQHandler(void);
void UART_SendString(const char *str);
void UART_SendNumber(uint32_t number);

#endif /*__BSP_USART_H_*/
