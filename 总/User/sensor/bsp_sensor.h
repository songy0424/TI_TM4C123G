#ifndef __BSP_SENSOR_H__
#define __BSP_SENSOR_H__

extern uint8_t L2_Val, L1_Val, M_Val, R1_Val, R2_Val;
extern int Line_Num;

void Followline_Init(void);
void Get_Line(void);
void GoStraight_control(void);

#endif /*__BSP_SENSOR_H__*/
