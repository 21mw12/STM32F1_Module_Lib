#ifndef __BOOTLOADER_H
#define __BOOTLOADER_H

///////////////////////////////////////////////////////////
//
// 文件功能：实现BootLoader功能，并通过类U-boot启动APP程序
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2025/02/16
// 注：不要单独使用，请使用模板
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * @brief 加载APP程序
  * @param App_Vector APP的烧录起始地址
  */
void BootLoader_LoadAPP(uint32_t App_Vector);

#endif
