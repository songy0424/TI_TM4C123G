/*
 * @Date: 2023-07-20 17:15:10
 * @LastEditTime: 2023-07-31 13:22:46
 * @Description: 帮助文件，查看引脚配置
 */
/**
 **********************************************************************************************************

//注释： 在函数介绍里面， 使用  ***   包含的为初始化函数
                        使用  ---   包含的为中断函数函数
                        使用  ...   包含的为可调用函数

1. qei（编码器读取）
  1-1 qei0（左轮）
    PHA --- PD6
    PHB --- PD7

  1-2 qei1（右轮）
    PHA --- PC5
    PHB --- PC6

  全部参数：
    *** short g_nMotorPulse *** 编码器1获取的值，在调用函数后清空
    *** short g_nMotor2Pulse *** 编码器2获取的值，在调用函数后清空
    *** long g_lMotorPulseSigma *** 编码器1获取的值的累加
    *** long g_lMotor2PulseSigma *** 编码器2获取的值的累加

  全部函数：
    *** void Qei_Init(void) ***
      参数说明：无
      函数介绍：初始化两个Qei模块
      使用方法：直接调用即可

    *** void GetMotorPulse(void) ***
      参数说明：无
      函数介绍：用于获取编码器的值，在获取时对任意一个编码器值取反，以获取相同的正方向，并且获取后清空他们的值
      使用方法：在定时器中断里面使用，例如使用40ms中断，然后在中断计算rpm


2. pwm（控制电机速度）
  2-1 pwm0（输出pwm）
    PWM3 --- PB5（左轮）
    PWM2 --- PB4（右轮）

  全部参数：

  全部函数：
    *** void Pwm_Init(void) ***
      参数说明：无
      函数介绍：初始化PWM模块，使用pwm0-2和pwm0-3控制电机速度
      使用方法：直接调用即可
      

3. usart（串口）
  3-1 usart0（调试PID）
    RX --- PA0（接TX）
    TX --- PA1

  3-2 usatr1（蓝牙通信）
    RX --- PB0（接TX）
    TX --- PB1

  3-3 usatr5（MPU传输数据）
    RX --- PE4（接TX）
    TX --- PE5

  3-4 usatr7（OPENMV通信） 
    RX --- PE0（接TX）
    TX --- PE1

  全部参数：

  全部函数：
    *** void Usart0_Init(void) ***
      参数说明：无
      函数介绍：初始化串口0，本串口用于PID的上位机调试
      使用方法：直接调用即可

    *** void Usart1_Init(void) ***
      参数说明：无
      函数介绍：初始化串口1，本串口用于双车间的蓝牙通信
      使用方法：直接调用即可

    *** void Usart5_Init(void) ***
      参数说明：无
      函数介绍：初始化串口5，本串口用于IMU901的通信，获取Yaw的值
      使用方法：直接调用即可

    *** void Usart7_Init(void) ***
      参数说明：无
      函数介绍：初始化串口7，本串口用于OPENMV通信
      使用方法：直接调用即可

    --- void USART0_IRQHandler(void) ---
      参数说明：无
      函数介绍：串口0的中断服务函数，中断里面写了获取上位机发送的数据，通过解析用于PID控制
      使用方法：在初始化时调用

    --- void USART1_IRQHandler(void) ---
      参数说明：无
      函数介绍：串口1的中断服务函数，暂时未使用
      使用方法：在初始化时调用

    --- void USART5_IRQHandler(void) ---
      参数说明：无
      函数介绍：串口5的中断服务函数，中断里面写了获取IMU发送的数据，通过解析获取Yaw的值
      使用方法：在初始化时调用

    --- void USART7_IRQHandler(void) ---
      参数说明：无
      函数介绍：串口7的中断服务函数，中断里面写了获取OPENMV发送的数据，通过解析获取真正的数据
      使用方法：在初始化时调用
   
    ··· uint8_t usart5_sendData(uint8_t *data, uint16_t len)···
      参数说明： uint8_t *data ：要发送的数据
                uint16_t len  ：数据长度
      函数介绍：串口5发送数据函数，用于和IMU通信
      使用方法：一般不使用，直接使用最外层封装
      返回值  ：发送成功返回0

    ··· uint16_t usart5_getRxData(uint8_t *buf, uint16_t len) ···
      参数说明： uint8_t *buf ：获取的数据存放的地址
                uint16_t len  ：数据长度
      函数介绍：接收串口5发送的数据，使用后调用另一函数，并把数据存放到自定义FIFO缓冲区
      使用方法：一般不使用，直接使用最外层封装
      返回值  ：返回FIFO实际读取个数

    ··· void UART_SendString(uint32_t ui32Base, const char *str) ···
      参数说明： uint32_t ui32Base ：串口基地址（如：UART0_BASE）
                const char *str   ：要发送的字符串
      函数介绍：发送字符串到任意串口
      使用方法：在串口初始化后，调用该函数并写入参数，即可向该串口发送数据


4. motor（电机驱动）
  4-1 left（左轮）
    IN1 --- PD2
    IN2 --- PD3
    
    O1 --- 从车轮方向看逆时针
    10 --- 从车轮方向看顺时针
    
  4-1 right（右轮）
    IN1 --- PD0
    IN2 --- PD1


5. iic（通信协议）
  5-1 iic0 （OLED显示）
    SCL --- PB2
    SDA --- PB3


6. timer（定时器）
  6-1 timer0（PID中断控制）
    无引脚

  6-2 systic（滴答定时器）
    无引脚


7. xunji（7路循迹）
  7-1 
    L2 --- PE2
    L1 --- PE3
    M  --- PF4   
    M1 --- PB6
    M2 --- PB7


8. key（按键）
  8-1
    KEY --- PF1 


9. beep（蜂鸣器）
  9-1
    BEEP --- PC4


  **********************************************************************************************************
*/