/*
 * @Date: 2023-07-28 17:48:19
 * @LastEditTime: 2023-07-29 12:49:52
 * @Description:
 */
#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

extern bool key_flag;

#define KeyPeripheral SYSCTL_PERIPH_GPIOF
#define KeyPort GPIO_PORTF_BASE
#define KeyPin GPIO_PIN_1
#define KeyInterrupt INT_GPIOF
#define KeyIntFlags GPIO_INT_PIN_1

void Key_Init(void);
void Key_IRQHandler(void);

#endif /*__BSP_KEY_H__*/
