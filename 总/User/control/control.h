/*
 * @Date: 2023-07-20 21:08:51
 * @LastEditTime: 2023-08-01 21:07:59
 * @Description:
 */
#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "main.h"

#define High 1
#define Low 0

/*限制最大速度*/
#define PWM_MAX_PERIOD_COUNT (1000 - 30)
#define PWM2_MAX_PERIOD_COUNT (1000 - 30)

/*编码器物理分辨率*/
#define ENCODER_RESOLUTION 11

/*经过倍频后的总分辨率*/
#define ENCODER_TOTAL_RESOLUTION (ENCODER_RESOLUTION * 4)

/*减速电机减速比*/
#define REDUCTION_RATIO 30

#define SPEED_PID_PERIOD 40  // 定时器0中断周期
#define TARGET_SPEED_MAX 120 // 最大速度限制

#define LUN_JU 17.5 // 单位cm

#define L_IN1(a) a ? GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2) \
                   : GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, ~GPIO_PIN_2)

#define L_IN2(a) a ? GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3) \
                   : GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, ~GPIO_PIN_3)

#define R_IN1(a) a ? GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0) \
                   : GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, ~GPIO_PIN_0)

#define R_IN2(a) a ? GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1) \
                   : GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, ~GPIO_PIN_1)

/*设置速度*/
#define SET_COMPAER(ChannelPulse) PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, ChannelPulse)
#define SET2_COMPAER(ChannelPulse) PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, ChannelPulse)

/*使能输出*/
#define MOTOR_ENABLE() PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT | PWM_OUT_3_BIT, true);

/*禁用输出*/
#define MOTOR_DISABLE() PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT | PWM_OUT_3_BIT, false);

typedef enum
{
    left_90,
    right_90,
    back_180
} spin_dir_t;

typedef enum
{
    MOTOR_FWD = 0, // 前进
    MOTOR_REV,     // 后退
} motor_dir_t;

void Timer0_IRQHandler(void);

float speed_pid_control(void);
float location_pid_control(void);
float speed2_pid_control(void);
float location2_pid_control(void);
void Location_Speed_control(void);

void Car_go(int32_t location_cm);
void spin_Turn(spin_dir_t zhuanxiang);

void MotorOutput(int nMotorPwm, int nMotor2Pwm);
void set_motor_speed(uint16_t v, uint16_t v2);
void set_motor_direction(motor_dir_t dir);
void set_motor2_direction(motor_dir_t dir);
void set_motor_enable(void);
void set_motor_disable(void);
void MotorGpio_Init(void);

#endif /*__CONTROL_H__*/
