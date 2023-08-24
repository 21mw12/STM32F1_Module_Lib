#include "PID_Location.h"

void PID_Location_Init(PID_Location_Struct* PID_Struct, float Kp, float Ki, float Kd) {
	PID_Struct->Kp = Kp;
	PID_Struct->Ki = Ki;
	PID_Struct->Kd = Kd;
	
	PID_Struct->err = 0.0;
	PID_Struct->err_last = 0.0;
	PID_Struct->err_sum = 0.0;
	
	PID_Struct->target = 0.0;
}

void PID_Location_SetTarget(PID_Location_Struct* PID_Struct, float newTarget) {
	PID_Struct->target = newTarget;
}

float PID_Location_Calculate(PID_Location_Struct* PID_Struct, float nowValue) {
	float result = 0.0;
	
	// ���㱾�����
	PID_Struct->err = PID_Struct->target - nowValue;
	
	// ����ۼ�
	PID_Struct->err_sum += PID_Struct->err;
	
	// PID����
	result = PID_Struct->Kp * PID_Struct->err + 
					 PID_Struct->Ki * PID_Struct->err_sum + 
					 PID_Struct->Kd * (PID_Struct->err - PID_Struct->err_last);
	
	// �������
	PID_Struct->err_last = PID_Struct->err;
	
	return result;
}
