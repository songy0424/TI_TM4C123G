#ifndef __BSP_QEI_H__
#define __BSP_QEI_H__

#include "main.h"

extern long g_lMotorPulseSigma;
extern long g_lMotor2PulseSigma;
extern short g_nMotorPulse, g_nMotor2Pulse;

void Qei_Init(void);
void GetMotorPulse(void);

#endif /*__BSP_QEI_H__*/
