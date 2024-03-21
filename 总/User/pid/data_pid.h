#ifndef __DATA_PID_H
#define __DATA_PID_H

#include "main.h"

typedef struct
{
	float target_val;
	float actual_val;
	double err;
	float err_last;
	float Kp, Ki, Kd;
	float integral;
} _pid;

extern _pid pid_speed, pid_speed2;
extern _pid pid_location, pid_location2;

void Pid_param_Init(void);
void set_pid_target(_pid *pid, float temp_val);
float get_pid_target(_pid *pid);
void set_p_i_d(_pid *pid, float p, float i, float d);

float location_pid_realize(_pid *pid, float actual_val);
float speed_pid_realize(_pid *pid, float actual_val);

#endif /*__DATA_PID_H */
