/*
 * @Date: 2023-07-10 20:44:10
 * @LastEditTime: 2023-08-01 20:34:36
 * @Description: 主函数
 */

#include "main.h"
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
#include "imu901.h"

u8g2_t u8g2;
float yaw;

uint16_t System_Time_ms = 0;
uint16_t ShowOLED_Time = 0;
uint8_t Send_Time = 0;
uint8_t Do_conut = 0;
uint8_t Stop_flag = 0;
char str3[50];
int main(void)
{
    All_Init();
    Car_go(100);
    while (1)
    {
        // receiving_process(); // PID上位机处理函数

        // if (Send_Time >= 21) // 发送数据到OPENMV和蓝牙
        // {
        //     Send_Time = 0;
        // }
        if (ShowOLED_Time >= 200) // OLED显示
        {
            ShowOLED_Time = 0;

            u8g2_ClearBuffer(&u8g2);
            sprintf(str3, "%d", Line_Num);
            u8g2_DrawStr(&u8g2, 10, 20, str3);

            u8g2_SendBuffer(&u8g2);
        }

        // switch (Do_conut)
        // {
        // case 0:
        //     Do_conut++;
        //     Car_go(50);
        //     break;

        // case 1:
        //     if (Stop_flag == 1)
        //     {
        //         Do_conut++;
        //         Car_go(20);
        //     }

        //     break;

        // default:
        //     break;
        // }

        // yaw = Imu901_GetYaw();
    }
}
