#ifndef __BSP_H__
#define __BSP_H__
/*
*********************************************************************************************************
*                                         ��׼��
*********************************************************************************************************
*/
#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <time.h>
#include  <stdint.h>
#include  <stdbool.h>


/*
*********************************************************************************************************
*                                         ������
*********************************************************************************************************
*/
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/udma.h"
#include "driverlib/timer.h"
#include "driverlib/i2c.h"
#include "driverlib/ssi.h"
#include "driverlib/debug.h"

#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_adc.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_i2c.h"
#include "inc/hw_uart.h"
#include "inc/hw_sysctl.h"



#include "utils/uartstdio.h"

/*
*********************************************************************************************************
*                                           OS��ϵͳ��
*********************************************************************************************************
*/
#include "system_TM4C123.h"

/*
*********************************************************************************************************
*                                        APP / BSP
*********************************************************************************************************
*/

#include "iic.h"
#include "oled.h"


/*
*********************************************************************************************************
*                                           �궨��
*********************************************************************************************************
*/   



/*
*********************************************************************************************************
*                                          �����ͺ���
*********************************************************************************************************
*/

#endif