#ifndef __BSP_BEEP_H__
#define __BSP_BEEP_H__

#define BeepPort GPIO_PORTC_BASE
#define BeepPin GPIO_PIN_4

void Beep_Init(void);
void Beep_Ring(int ms);

#endif /*__BSP_BEEP_H__*/
