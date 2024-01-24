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

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	
	float err;				// 当前误差
	float err_last;		// 上一次误差
	float err_pass;		// 上上次误差
	
	float target;			// 目标值
} PID_Incremental_Struct;

/**
  * @brief 增量式PID初始化
  * @param pid PID结构体
  * @param Kp p值
  * @param Ki i值
  * @param Kd d值
  * @return 无
  */
void PID_Incremental_Init(PID_Incremental_Struct* pid, float Kp, float Ki, float Kd);

/**
  * @brief 增量式PID设置目标值
  * @param pid PID结构体
  * @param NewTarget 当前目标
  * @return 无
  */
void PID_Incremental_SetTarget(PID_Incremental_Struct* pid, float NewTarget);

/**
  * @brief 增量式PID计算
  * @param pid PID结构体
  * @param NowValue 当前值
  * @return 增量结果
  */
float PID_Incremental_Calculate(PID_Incremental_Struct* pid, float NowValue);

#endif
