/*
 * @Date: 2023-07-18 14:37:09
 * @LastEditTime: 2023-07-18 21:24:59
 * @Description: ���ô��ں���
 */
#include "bsp_usart.h"

void USART0_IRQHandler(void);

/**
 * @brief ���ڳ�ʼ������
 * @return {*}
 */
void USART_Config(void)
{
    // ʹ������
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // ʹ�ܸ���
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    // �����ź�
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1);

    // ���ô���0��������У��λ��ֹͣλ���ֳ���
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    // ʹ��FIFO
    UARTFIFOEnable(UART0_BASE);

    /*
        FIFO�����������1/8��1/4��1/2��3/4��7/8����
        ���磬���ý���FIFIO���Ϊ1/8����ô����FIFO��װ����16*1/8=2�ֽ�ʱ�����ж�
        �������FIFO����ôÿ����һ���ֽڶ�Ҫ����һ���жϣ�����Ƶ���Ľ����ж�
    */

    // ���շ��͵�FIFO��Ϊ1/8��Ҳ����16*1/8=2���ֽ�
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

    // ʹ�ܴ��ڵĽ�������ճ�ʱ�ж�
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    // ע���жϺ���
    UARTIntRegister(UART0_BASE, USART0_IRQHandler);

    // �����ж����ȼ����ж����ȼ���8����0���
    IntPrioritySet(INT_UART0, 2);

    // �����ж�
    IntEnable(INT_UART0);
    IntMasterEnable();

    // ʹ�ܴ���
    UARTEnable(UART0_BASE);
}

/**
 * @brief �����жϺ��������������������
 * @return {*}
 */

void USART0_IRQHandler(void)
{
    uint32_t re_buf;

    // ��ȡ�ж�״̬
    uint32_t status = UARTIntStatus(UART0_BASE, true);

    // ����жϱ�־λ
    UARTIntClear(UART0_BASE, status);

    // �ж�UART0��û���ַ�δ��ȡ
    while (UARTCharsAvail(UART0_BASE))
    {
        // ������ַ�Ϊ��ȡ��ȡ����ʹ��UARTCharGetNonBlocking��ֹ�ȴ�
        re_buf = UARTCharGetNonBlocking(UART0_BASE);
        // ����ȡ�����ַ��ٷ���
        UARTCharPutNonBlocking(UART0_BASE, re_buf); // ��ָ���˿ڷ����ַ���
    }
}

void UART_SendString(const char *str)
{
    while (*str)
    {
        // �ȴ����ͻ�����Ϊ��
        while (UARTSpaceAvail(UART0_BASE) == false)
        {
        }
        // ����һ���ַ�
        UARTCharPut(UART0_BASE, *str++);
    }
}

void UART_SendNumber(uint32_t number)
{
    char buffer[16];        // ���ڴ洢ת������ַ�����
    uint8_t digitCount = 0; // ����λ��

    // ������ת��Ϊ�ַ�����
    do
    {
        buffer[digitCount++] = '0' + (number % 10); // ��ÿ������ת��Ϊ�ַ�
        number /= 10;
    } while (number > 0);

    // �����ַ����飨�����ͣ�
    while (digitCount > 0)
    {
        digitCount--;

        // �ȴ����ͻ�����Ϊ��
        while (UARTSpaceAvail(UART0_BASE) == false)
        {
        }

        // ����һ���ַ�
        UARTCharPut(UART0_BASE, buffer[digitCount]);
    }
}
