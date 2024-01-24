#include "PID_Incremental.h"

void PID_Incremental_Init(PID_Incremental_Struct* pid, float Kp, float Ki, float Kd) {
	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;
	
	pid->err = 0.0;
	pid->err_last = 0.0;
	pid->err_pass = 0.0;
	
	pid->target = 0.0;
}

void PID_Incremental_SetTarget(PID_Incremental_Struct* pid, float newTarget) {
	pid->target = newTarget;
}

float PID_Incremental_Calculate(PID_Incremental_Struct* pid, float nowValue) {
	float Increment = 0.0;

	/* 计算本次误差 */
	pid->err = pid->target - nowValue;

	/* PID计算 */
	Increment = pid->Kp * (pid->err - pid->err_last) + 
							pid->Ki * pid->err + 
							pid->Kd * (pid->err - 2 * pid->err_last + pid->err_pass);

	/* 传递误差 */
	pid->err_pass = pid->err_last;
	pid->err_last = pid->err;
	
	return Increment;
}
