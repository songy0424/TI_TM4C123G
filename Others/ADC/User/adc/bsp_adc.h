#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "main.h"

void adc_init(uint32_t adc_base, uint32_t gpio_base, uint32_t pin, uint32_t channel, uint32_t sequence, int average_num);
unsigned long ADC_ValueGet(uint32_t ui32Base, uint32_t ui32SequenceNum);

#endif /*__BSP_ADC_H__*/
