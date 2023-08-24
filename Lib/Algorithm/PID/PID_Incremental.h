#ifndef __PID_INCREMENTAL_H
#define __PID_INCREMENTAL_H

///////////////////////////////////////////////////////////
//
// 文件功能：增量式PID
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/08/24
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	
	float err;				// 当前误差
	float err_last;		// 上一次误差
	float err_pass;		// 上上次误差
	
	float target;			// 目标值
} PID_Incremental_Struct;

void PID_Incremental_Init(PID_Incremental_Struct* PID_Struct, float Kp, float Ki, float Kd);

void PID_Incremental_SetTarget(PID_Incremental_Struct* PID_Struct, float newTarget);

float PID_Incremental_Calculate(PID_Incremental_Struct* PID_Struct, float nowValue);

#endif
