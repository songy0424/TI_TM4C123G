/*
 * @Date: 2023-07-10 21:43:59
 * @LastEditTime: 2023-07-30 17:19:08
 * @Description:头文件及宏定义
 */

/*
*********************************************************************************************************
*                                         标准库
*********************************************************************************************************
*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
/*
*********************************************************************************************************
*                                         其它库
*********************************************************************************************************
*/
#include "sysctl.h"
#include "systick.h"
#include "gpio.h"
#include "adc.h"
#include "uart.h"
#include "interrupt.h"
#include "pin_map.h"
#include "pwm.h"
#include "udma.h"
#include "timer.h"
#include "qei.h"
#include "i2c.h"

#include "hw_gpio.h"
#include "hw_memmap.h"
#include "hw_adc.h"
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_i2c.h"

/*
*********************************************************************************************************
*                                        自定义文件
*********************************************************************************************************
*/
#include "init.h"
#include "oled.h"
#include "bsp_qei.h"
#include "bsp_timer.h"
#include "data_pid.h"
#include "bsp_pwm.h"
#include "bsp_usart.h"
#include "Fire_protocol.h"
#include "control.h"
#include "bsp_sys.h"
#include "bsp_key.h"
#include "bsp_beep.h"
#include "u8g2.h"
#include "iic.h"
#include "bsp_openmv.h"
#include "imu901.h"
#include "bsp_sensor.h"
