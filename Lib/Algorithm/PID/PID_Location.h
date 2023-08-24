#ifndef __PID_LOCATION_H
#define __PID_LOCATION_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�λ��ʽPID
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/08/24
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	
	float err;				// ��ǰ���
	float err_last;		// ��һ�����
	float err_sum;		// ����
	
	float target;			// Ŀ��ֵ
} PID_Location_Struct;

void PID_Location_Init(PID_Location_Struct* PID_Struct, float Kp, float Ki, float Kd);

void PID_Location_SetTarget(PID_Location_Struct* PID_Struct, float newTarget);

float PID_Location_Calculate(PID_Location_Struct* PID_Struct, float nowValue);

#endif
