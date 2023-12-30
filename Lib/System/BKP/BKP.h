#ifndef __BKP_H
#define __BKP_H

///////////////////////////////////////////////////////////

// 文件功能：BPK的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/12/30
//
// 注：需要给VBAT引脚一个1.8~3.6V的电源
//		 小和中容量有20字节 / 大容量和互联型有84字节
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * @brief BKP初始化
  * @return 无
  */
void BKP_Init(void);

/**
  * @brief 写入BKP
  * @param BKP_Add BKP的地址
  * @param Data 要写入的数据
  * @return 无
  */
#define BKP_Write(BKP_Add, Data)		BKP_WriteBackupRegister(BKP_Add, Data)

/**
  * @brief 读出BKP
  * @param BKP_Add BKP的地址
  * @return 对应地址中的数据
  */
#define BKP_Read(BKP_Add)						BKP_ReadBackupRegister(BKP_Add)

#endif
