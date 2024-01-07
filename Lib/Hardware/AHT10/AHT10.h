#ifndef __AHT10_H
#define __AHT10_H

///////////////////////////////////////////////////////////
//
// 文件功能：AHT10温湿度传感器模块的功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/06
//
// 注：代码思路来自于https://zhuanlan.zhihu.com/p/582329736
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* AHT10 I2C地址 */
#define AHT10_ADDRESS			0x38 << 1

typedef enum {
	AHT10_State_Error = 0,
	AHT10_State_Normal
} AHT10_State;

/**
  * @brief AHT10初始化
  * @return 
  */
void AHT10_Init(void);

/**
  * @brief 软件复位AHT10
  * @return 
  */
void AHT10_SoftReset(void);

/**
  * @brief 获取AHT10温湿度数据
  * @param Temp 温度值
  * @param Hum 湿度值
  * @return AHT0读取状态
  */
AHT10_State AHT10_GetData(float *Temp, float *Hum);

#endif
