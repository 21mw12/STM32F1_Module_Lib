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

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	
	float err;				// 当前误差
	float err_last;		// 上一次误差
	float err_sum;		// 误差和
	
	float target;			// 目标值
} PID_Location_Struct;

/**
  * @brief 增量式PID初始化
  * @param pid PID结构体
  * @param Kp p值
  * @param Ki i值
  * @param Kd d值
  * @return 无
  */
void PID_Location_Init(PID_Location_Struct* pid, float Kp, float Ki, float Kd);

/**
  * @brief 增量式PID设置目标值
  * @param pid PID结构体
  * @param NewTarget 当前目标
  * @return 无
  */
void PID_Location_SetTarget(PID_Location_Struct* pid, float NewTarget);

/**
  * @brief 增量式PID计算
  * @param pid PID结构体
  * @param NowValue 当前值
  * @return 增量结果
  */
float PID_Location_Calculate(PID_Location_Struct* pid, float NowValue);

#endif
