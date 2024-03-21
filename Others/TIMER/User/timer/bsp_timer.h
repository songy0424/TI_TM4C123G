#ifndef __BSP_TIMER_H__
#define __BSP_TIMER_H__

#include "main.h"

extern _Bool flag;

void Timer_Config(void);
void TIMER_IRQHandler(void);
void Timer_Wid_Config(void);
void TIMER_WID_IRQHandler(void);

#endif /*__BSP_TIMER_H__*/
