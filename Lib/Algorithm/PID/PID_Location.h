#ifndef __PID_LOCATION_H
#define __PID_LOCATION_H

///////////////////////////////////////////////////////////
//
// 文件功能：位置式PID
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
	float err_sum;		// 误差和
	
	float target;			// 目标值
} PID_Location_Struct;

void PID_Location_Init(PID_Location_Struct* PID_Struct, float Kp, float Ki, float Kd);

void PID_Location_SetTarget(PID_Location_Struct* PID_Struct, float newTarget);

float PID_Location_Calculate(PID_Location_Struct* PID_Struct, float nowValue);

#endif
