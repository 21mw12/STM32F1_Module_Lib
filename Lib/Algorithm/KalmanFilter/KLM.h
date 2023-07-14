#ifndef __KLM_H
#define __KLM_H

///////////////////////////////////////////////////////////
//
// 文件功能：卡尔曼滤波器
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/07/14
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
	* 解释：
	* 	Q表示的是噪音。
	*			├ 是不可测量不可消除的参数。
	*			└ 是需要调节的参数。 
	*
	*		R表示的是测量的协方差矩阵。
	*			├ R越大，表示测量值不可靠，更相信估计值。（太大会让传感器反应迟钝）
	*			├ R越小，表示估计值不可靠，更相信测量值。（过小锯齿状会更明显）
	*			└ R = 0，表示只相信实际值。（没有滤波）
	*/
typedef struct {
	float P;		// 后验误差协方差
	float P_;		// 先验误差协方差
	float X;		// 先验估计
	float X_;		// 后验估计
	float K;		// 卡尔曼增益
	float Q;		// 噪音
	float R;		// 测量的协方差矩阵
} KLM_Struct;

/**
  * @brief 初始化卡尔曼滤波器的参数
  * @param klm 卡尔曼滤波器结构体
  * @param Q_Set 噪音
  * @param R_Set 测量的协方差矩阵
  * @return 无
  */
void KLM_Struct_Init(KLM_Struct* klm, float Q_Set, float R_Set);

/**
  * @brief 卡尔曼滤波器计算
  * @param klm 卡尔曼滤波器结构体
  * @param Z 测量值
  * @return 滤波推导后的计算值
  */
float KalmanFilter(KLM_Struct* klm, float Z);

#endif
