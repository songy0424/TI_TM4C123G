/*
 * @Date: 2023-07-18 19:21:54
 * @LastEditTime: 2023-08-01 21:12:23
 * @Description: 各传感器配置，包括循迹
 * 只有Line_Num是有用的，为巡线补偿值
 */
#include "main.h"

uint8_t L2_Val, L1_Val, M_Val, R1_Val, R2_Val;
int Line_Num = 0;

/**
 * @brief 五路循迹初始化
 * @return
 */

void Followline_Init(void)
{
    // 开启端口外设
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // 配置为上拉输入
    GPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_6 | GPIO_PIN_7, GPIO_DIR_MODE_IN);

    GPIODirModeSet(GPIO_PORTE_BASE, GPIO_PIN_2 | GPIO_PIN_3, GPIO_DIR_MODE_IN);
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);

    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_6 | GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

/**
 * @brief 读取循迹串口值
 * @return
 */
void Get_Line(void)
{
    R1_Val = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_7);
    R2_Val = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_6);
    L2_Val = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);
    L1_Val = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2);
    M_Val = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
}

/**
 * @brief 判断补偿
 * @return
 */
void GoStraight_control(void)
{
    Get_Line();
    if (L1_Val == 0 && L2_Val == 0 && M_Val != 0 && R1_Val == 0 && R2_Val == 0) // 只有中间检测到黑线
        Line_Num = 0;

    // 偏左的情况
    if (L1_Val == 0 && L2_Val != 0 && M_Val != 0 && R1_Val == 0 && R2_Val == 0) // 左1、中
        Line_Num = -50;
    if (L1_Val == 0 && L2_Val != 0 && M_Val == 0 && R1_Val == 0 && R2_Val == 0) // 左1
        Line_Num = -100;
    if (L1_Val != 0 && L2_Val != 0 && M_Val == 0 && R1_Val == 0 && R2_Val == 0) // 左1、左2
        Line_Num = -150;
    if (L1_Val != 0 && L2_Val == 0 && M_Val == 0 && R1_Val == 0 && R2_Val == 0) // 左2
        Line_Num = -300;

    // 偏右的情况
    if (L1_Val == 0 && L2_Val == 0 && M_Val != 0 && R1_Val != 0 && R2_Val == 0) // 右1，中
        Line_Num = 50;
    if (L1_Val == 0 && L2_Val == 0 && M_Val == 0 && R1_Val != 0 && R2_Val == 0) // 右1
        Line_Num = 100;
    if (L1_Val == 0 && L2_Val == 0 && M_Val == 0 && R1_Val != 0 && R2_Val != 0) // 右1、右2
        Line_Num = 150;
    if (L1_Val == 0 && L2_Val == 0 && M_Val == 0 && R1_Val == 0 && R2_Val != 0) // 右2
        Line_Num = 300;
}
