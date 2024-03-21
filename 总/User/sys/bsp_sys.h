#ifndef __BSP_SYS_H__
#define __BSP_SYS_H__

extern uint16_t System_Time_ms;

void SysTick_IRQHandler(void);
void SysTick_Init(void);
void Delay_ms(int count);

#endif /*__BSP_SYS_H__*/
