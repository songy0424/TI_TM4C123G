/*
 * @Date: 2023-07-17 19:20:50
 * @LastEditTime: 2023-07-18 14:20:51
 * @Description:PWM��ʼ��
 */
#include "bsp_pwm.h"

void PWM_Config(void)
{
    // ��Ϊ������ʱ��������40MHz�������������һ��Ƶ����Ϊ4��Ƶ����ôPWMʱ�Ӿ���10MHz
    SysCtlPWMClockSet(SYSCTL_PWMDIV_4); // ������ʱ�ӽ��к����Ƶ����ΪPWMʱ��

    // ʹ��GPIOF��PWM1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);

    // ΪGPIOF_PIN_2��GPIOF_PIN_3����PWM�ź�
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2); // Ϊ���ŷ���PWM�ź�
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);

    // ��GPIOF_PIN_2��GPIOF_PIN_3ʹ�����Ÿ���
    GPIOPinConfigure(GPIO_PF2_M1PWM6); // ʹ�ܸ���
    GPIOPinConfigure(GPIO_PF3_M1PWM7);

    // ����PWM1ģ��ĵ��ĸ�������Ϊ���¼����벻ͬ������
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC); // ����PWM������

    // ����PWM1ģ��ĵ��ĸ�������ÿ����������Ϊ1000��������PWMʱ��Ϊ10MHz����ôPWM���Ƶ�ʾ���10 ^ 7 / 1000Ϊ10KHz�����ܳ���65535
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 1000); // ����PWM���Ƶ��

    // ����PWM1ģ��ĵ�����ͨ����ռ�ձ�Ϊ10%����������ĵ���������Ϊ�����ڵĸߵ�ƽ�������Կ���ͨ��PWMGenPeriodGet(��ȡPWM������ģ�������)�ó�һ�������ڵļ��������ٳ�0.1Ȼ���1����
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) * 0.1 - 1); // ����PWM���ռ�ձ�
    // ͬ��ֻ���������õ��߸�ͨ��
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) * 0.1 - 1);

    // ʹ�ܵ�����ͨ��
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true); // ʹ�����ͨ��
    // ʹ�ܵ��߸�ͨ��
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true); // ʹ�ܷ�����

    // ʹ�ܵ�����������
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
}

// �Զ��庯����������ռ�ձ�
void PWM_duty(uint32_t ui32Base, uint32_t ui32PWMOut, uint32_t ui32PWMOutBits, uint32_t ui32Gen, float duty)
{
    PWMPulseWidthSet(ui32Base, ui32PWMOut, PWMGenPeriodGet(ui32Base, ui32Gen) * duty - 1);
}
