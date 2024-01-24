#include "PID_Location.h"

void PID_Location_Init(PID_Location_Struct* pid, float Kp, float Ki, float Kd) {
	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;
	
	pid->err = 0.0;
	pid->err_last = 0.0;
	pid->err_sum = 0.0;
	
	pid->target = 0.0;
}

void PID_Location_SetTarget(PID_Location_Struct* pid, float newTarget) {
	pid->target = newTarget;
}

float PID_Location_Calculate(PID_Location_Struct* pid, float nowValue) {
	float result = 0.0;
	
	/* ���㱾����� */
	pid->err = pid->target - nowValue;
	
	/* ����ۼ� */
	pid->err_sum += pid->err;
	
	/* PID���� */
	result = pid->Kp * pid->err + 
					 pid->Ki * pid->err_sum + 
					 pid->Kd * (pid->err - pid->err_last);
	
	/* ������� */
	pid->err_last = pid->err;
	
	return result;
}
