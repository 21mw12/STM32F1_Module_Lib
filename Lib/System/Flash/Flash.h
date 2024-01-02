#ifndef __FLASH_H
#define __FLASH_H

///////////////////////////////////////////////////////////
//
// 文件功能：片内Flash的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/02
//
// 注：使用Flash存储数据时要优先使用最后一页，防止覆盖程序数据
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * @brief 向Flash中写入一个字（32位）
  * @param Address Flash的地址
  * @param Data 写入的数据
  * @return 无
  */
void FLASH_WriteWord(uint32_t Address, uint32_t Data);

/**
  * @brief 向Flash中写入一个半字（16位）
  * @param Address Flash的地址
  * @param Data 写入的数据
  * @return 无
  */
void FLASH_WriteHalfWord(uint32_t Address, uint16_t Data);

/**
  * @brief 从Flash中读出一个字（32位）
  * @param Address Flash的地址
  * @return 读出的数据
  */
uint32_t FLASH_ReadWord(uint32_t Address);

/**
  * @brief 从Flash中读出一个半字（16位）
  * @param Address Flash的地址
  * @return 读出的数据
  */
uint16_t FLASH_ReadHalfWord(uint32_t Address);

/**
  * @brief 从Flash中读出一个字节（8位）
  * @param Address Flash的地址
  * @return 读出的数据
  */
uint8_t FLASH_ReadByte(uint32_t Address);

/**
  * @brief 擦除所有Flash内容
  * @return 无
  */
void FLASH_ClearAllPages(void);

/**
  * @brief 擦除所有Flash的一页
  * @param PageAddress Flash页的首地址
  * @return 无
  */
void FLASH_ClearPage(uint32_t PageAddress);

/**
  * @brief 获取Flash大小
  * @return Flash大小
  */
uint16_t FLASH_GetSTM32_FLASHSIZE(void);

/**
  * @brief 获取STM32芯片的ID号
  * @param ChipID0 ID号最底位
  * @param ChipID1 ID号中间位
  * @param ChipID2 ID号最高高
  * @return 无
  */
void FLASH_GetSTM32_ChipID(uint32_t* ChipID0, uint32_t* ChipID1, uint32_t* ChipID2);

#endif
