#include "PID_Incremental.h"

void PID_Incremental_Init(PID_Incremental_Struct* PID_Struct, float Kp, float Ki, float Kd) {
	PID_Struct->Kp = Kp;
	PID_Struct->Ki = Ki;
	PID_Struct->Kd = Kd;
	
	PID_Struct->err = 0.0;
	PID_Struct->err_last = 0.0;
	PID_Struct->err_pass = 0.0;
	
	PID_Struct->target = 0.0;
}

void PID_Incremental_SetTarget(PID_Incremental_Struct* PID_Struct, float newTarget) {
	PID_Struct->target = newTarget;
}

float PID_Incremental_Calculate(PID_Incremental_Struct* PID_Struct, float nowValue) {
	float Increment = 0.0;

	// 计算本次误差
	PID_Struct->err = PID_Struct->target - nowValue;

	// PID计算
	Increment = PID_Struct->Kp * (PID_Struct->err - PID_Struct->err_last) + 
							PID_Struct->Ki * PID_Struct->err + 
							PID_Struct->Kd * (PID_Struct->err - 2 * PID_Struct->err_last + PID_Struct->err_pass);

	// 传递误差
	PID_Struct->err_pass = PID_Struct->err_last;
	PID_Struct->err_last = PID_Struct->err;
	
	return Increment;
}
