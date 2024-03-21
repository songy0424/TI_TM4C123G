#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__

#include "main.h"

void PWM_Config(void);
void PWM_duty(uint32_t ui32Base, uint32_t ui32PWMOut, uint32_t ui32PWMOutBits, uint32_t ui32Gen, float duty);

#endif /*__BSP_PWM_H__*/
