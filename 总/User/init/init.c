/*
 * @Date: 2023-07-10 20:44:10
 * @LastEditTime: 2023-08-01 19:57:16
 * @Description: 全部初始化配置函数
 * 把初始化函数都放在该文件即可
 */
#include "main.h"

/**
 * @brief 全部初始化函数
 * @return
 */
void All_Init(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_8MHZ | SYSCTL_OSC_MAIN); // 设置时钟总线为50MHz

    U8g2_Init(&u8g2); // U8G2-OLED初始化
    MotorGpio_Init(); // 电机引脚初始化
    Qei_Init();       // QEI初始化
    Pwm_Init();       // PWM初始化
    Pid_param_Init(); // PID参数初始化

    // Usart5_Init();    // 串口5通信
    // Imu901_Init();    // IMU901初始化

    // Usart1_Init(); // 串口1初始化
    // Usart7_Init(); // 串口7初始化

    // Key_Init();  // 按键初始化
    // Beep_Init(); // 蜂鸣器初始化
    Followline_Init(); // 5路循迹初始化
    SysTick_Init();    // 系统定时器初始化

    // Protocol_init(); // 上位机协议初始化
    // Usart0_Init();   // 串口0初始化
    set_motor_enable();
    Timer0_Init(); // 定时器0初始化
}
