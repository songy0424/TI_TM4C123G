/*
 * @Date: 2023-07-20 14:30:41
 * @LastEditTime: 2023-07-20 16:54:48
 * @Description: ADC读取电压
 */

#include "main.h"
#include "oled.h"
#include "u8g2.h"
#include "bsp_adc.h"

char numberStr[50]; // 足够大的字符数组来存储转换后的字符串
uint16_t value;

int main(void)
{ // 设置时钟总线是40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    u8g2_t u8g2;
    u8g2Init(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_t0_15_mr); // 10*10

    adc_init(ADC0_BASE, GPIO_PORTE_BASE, GPIO_PIN_0, 3, ADC_CTL_CH3, 8);

    while (1)
    {
        value = ADC_ValueGet(ADC0_BASE, 3);
        Delay_ms(100);
        sprintf(numberStr, "%4d", value);
        u8g2_DrawStr(&u8g2, 20, 30, numberStr);
        u8g2_SendBuffer(&u8g2);
    }
}
