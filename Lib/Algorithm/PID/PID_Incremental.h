#ifndef __PID_INCREMENTAL_H
#define __PID_INCREMENTAL_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�����ʽPID
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
	float err_pass;		// ���ϴ����
	
	float target;			// Ŀ��ֵ
} PID_Incremental_Struct;

void PID_Incremental_Init(PID_Incremental_Struct* PID_Struct, float Kp, float Ki, float Kd);

void PID_Incremental_SetTarget(PID_Incremental_Struct* PID_Struct, float newTarget);

float PID_Incremental_Calculate(PID_Incremental_Struct* PID_Struct, float nowValue);

#endif
