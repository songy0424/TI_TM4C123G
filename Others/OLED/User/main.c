/*
 * @Date: 2023-07-10 20:44:10
 * @LastEditTime: 2023-07-19 22:17:52
 * @Description: OLED显示数字字符或图像
 */

#include "main.h"
#include "oled.h"
#include "u8g2.h"

int main(void)
{ // 设置时钟总线是40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    u8g2_t u8g2;
    u8g2Init(&u8g2);
    // u8g2_SetFont(&u8g2, u8g2_font_inr16_mr);
    while (1)
    {
        u8g2_DrawCircle(&u8g2, 30, 32, 25, U8G2_DRAW_ALL);
        u8g2_DrawCircle(&u8g2, 64, 32, 25, U8G2_DRAW_ALL);
        u8g2_DrawCircle(&u8g2, 98, 32, 25, U8G2_DRAW_ALL);

        // u8g2_DrawStr(&u8g2, 30, 30, "HELLO!");
        u8g2_SendBuffer(&u8g2);
    }
}
