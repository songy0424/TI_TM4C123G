/*
 * @Date: 2023-07-18 14:37:09
 * @LastEditTime: 2023-07-18 15:35:01
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

    /*����UARTprintfʹ��*/
    // ���ô���0��ʱ��ΪUART_CLOCK_PIOSC
    //	UARTClockSourceSet( UART0_BASE,  UART_CLOCK_PIOSC);
    // ���ô���0�������벨��ʱ��
    //	UARTStdioConfig(0, 115200, 16000000);
    /*��UARTCharPut��UARTCharPutNonBlocking�ȴ���ʹ��*/

    // ���ô���0��������У��λ��ֹͣλ���ֳ���
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    // ʹ��FIFO
    UARTFIFOEnable(UART0_BASE);

    /*
        FIFO�����������1/8��1/4��1/2��3/4��7/8����
        ���磬���ý���FIFIO���Ϊ1/8����ô����FIFO��װ����16*1/8=2�ֽ�ʱ�����ж�
        �������FIFO����ôÿ����һ���ֽڶ�Ҫ����һ���жϣ�����Ƶ���Ľ����ж�
    */

    // ���շ��͵�FIFO��Ϊ1/4��Ҳ����16*1/4=4���ֽ�
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX2_8, UART_FIFO_RX2_8);

    // ʹ�ܴ��ڵĽ�������ճ�ʱ�ж�
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    // ע���жϺ���
    UARTIntRegister(UART0_BASE, USART0_IRQHandler);

    // �����ж����ȼ����ж����ȼ���8����0���
    IntPrioritySet(INT_UART0, 0);

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
