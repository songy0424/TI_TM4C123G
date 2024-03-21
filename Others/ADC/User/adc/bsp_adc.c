/*
 * @Date: 2023-07-19 16:47:02
 * @LastEditTime: 2023-07-20 16:53:24
 * @Description: ADC初始化
 */
#include "bsp_adc.h"

void adc_init(uint32_t adc_base, uint32_t gpio_base, uint32_t pin, uint32_t channel, uint32_t sequence, int average_num)
{
    uint32_t adc_gpio;

    switch (gpio_base) // 选择GPIO
    {
    case GPIO_PORTA_BASE:
    {
        adc_gpio = SYSCTL_PERIPH_GPIOA;
        break;
    }
    case GPIO_PORTB_BASE:
    {
        adc_gpio = SYSCTL_PERIPH_GPIOB;
        break;
    }
    case GPIO_PORTC_BASE:
    {
        adc_gpio = SYSCTL_PERIPH_GPIOC;
        break;
    }
    case GPIO_PORTD_BASE:
    {
        adc_gpio = SYSCTL_PERIPH_GPIOD;
        break;
    }
    case GPIO_PORTE_BASE:
    {
        adc_gpio = SYSCTL_PERIPH_GPIOE;
        break;
    }
    case GPIO_PORTF_BASE:
    {
        adc_gpio = SYSCTL_PERIPH_GPIOF;
        break;
    }
    }
    if (adc_base == ADC0_BASE)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // 使能ADC0
    if (adc_base == ADC1_BASE)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1); // 使能ADC1

    SysCtlPeripheralEnable(adc_gpio);                                   // 使能GPIO
    GPIOPinTypeADC(gpio_base, pin);                                     // 选择管脚
    ADCSequenceConfigure(adc_base, sequence, ADC_TRIGGER_PROCESSOR, 0); // sequence: 选择序列; 最后一个参数: 优先级
    ADCHardwareOversampleConfigure(adc_base, average_num);              // average_num 个数取一次均值
    ADCSequenceStepConfigure(adc_base, sequence, 0, channel | ADC_CTL_IE | ADC_CTL_END);

    ADCSequenceEnable(adc_base, sequence); // 使能一个采样序列
    ADCIntClear(adc_base, sequence);       // 清除采样序列中断源
}

/************************************************************************
 * @brief   获取特定ADC的转化采样值。
 * @param   ui32Base            ADC采样基地址
 * @param   ui32SequenceNum     AD采样序列号
 * @return  ADC采样值
 ***********************************************************************/
unsigned long ADC_ValueGet(uint32_t ui32Base, uint32_t ui32SequenceNum)
{
    static unsigned long value = 0;
    static uint32_t ADCValue[1]; // 保存ADC采样值

    ADCProcessorTrigger(ui32Base, ui32SequenceNum); // 触发获取端口采样
    while (!ADCIntStatus(ui32Base, ui32SequenceNum, false))
        ;                                                    // 等待采样结束
    ADCIntClear(ui32Base, ui32SequenceNum);                  // 清除ADC采样中断标志
    ADCSequenceDataGet(ui32Base, ui32SequenceNum, ADCValue); // 读取ADC采样值

    value = ADCValue[0];
    return value;
}
