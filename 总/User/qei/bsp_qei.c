/*
 * @Date: 2023-07-18 19:21:54
 * @LastEditTime: 2023-07-31 22:24:44
 * @Description: QEI配置，获取编码器值
 */

#include "bsp_qei.h"

long g_lMotorPulseSigma = 0;
long g_lMotor2PulseSigma = 0;
short g_nMotorPulse = 0, g_nMotor2Pulse = 0;

/**
 * @brief QEI初始化，可以获取编码器值
 * @return
 */
void Qei_Init(void)
{
    // 使能QEI相关GPIO引脚
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    // 使能QEI模块时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);

    // 配置GPIO引脚为QEI功能
    GPIOPinConfigure(GPIO_PC5_PHA1);
    GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_5);

    GPIOPinConfigure(GPIO_PC6_PHB1);
    GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_6);

    GPIOPinConfigure(GPIO_PD6_PHA0);
    GPIOPinTypeQEI(GPIO_PORTD_BASE, GPIO_PIN_6);

    // 解锁引脚配置
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0x80;

    GPIOPinConfigure(GPIO_PD7_PHB0);
    GPIOPinTypeQEI(GPIO_PORTD_BASE, GPIO_PIN_7);

    // 配置GPIO引脚的电气特性
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_7, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);

    // 配置QEI模块
    QEIConfigure(QEI1_BASE, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), 65535);
    QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), 65535);

    // 配置QEI模块的位置计数初始值
    QEIPositionSet(QEI0_BASE, 0);
    QEIPositionSet(QEI1_BASE, 0);

    // 使能QEI模块
    QEIEnable(QEI0_BASE);
    QEIEnable(QEI1_BASE);
}

void GetMotorPulse(void)
{
    g_nMotorPulse = (short)QEIPositionGet(QEI0_BASE);
    QEIPositionSet(QEI0_BASE, 0);

    g_nMotor2Pulse = (short)QEIPositionGet(QEI1_BASE);
    QEIPositionSet(QEI1_BASE, 0);

    g_lMotorPulseSigma += g_nMotorPulse;
    g_lMotor2PulseSigma += g_nMotor2Pulse;
}
