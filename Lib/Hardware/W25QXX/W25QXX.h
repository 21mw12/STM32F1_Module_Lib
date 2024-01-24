#ifndef __W25QXX_H
#define __W25QXX_H

///////////////////////////////////////////////////////////
//
// 文件功能：W25QXX系列芯片
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/12/27
//
// 注：在江协科技的代码基础上做通用性的修改
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* W25QXX芯片端口信息 */
#define W25QXX_GPIOPeriph		RCC_APB2Periph_GPIOA
#define W25QXX_Port					GPIOA
#define W25QXX_Pin_CS				GPIO_Pin_4

/**
  * @brief W25QXX系列芯片初始化
  * @return 无
  */
void W25QXX_Init(void);

/**
  * @brief W25QXX芯片读ID
  * @param MID 厂商ID
  * @param DID 设备ID
  * @return 无
  */
void W25QXX_ReadID(uint8_t* MID, uint16_t* DID);

/**
  * @brief W25QXX芯片解除写保护
  * @return 无
  */
void W25QXX_RelieveWriteProtect(void);

/**
  * @brief W25QXX芯片写数据
  * @param address 写入页地址（xxxx00~xxxxFF）
  * @param dataArray 写入数据数组
  * @param count 写入数据数量（最多写256个，超过会覆盖第一个）
  * @return 无
	* 注：如果写数据前不擦除会使得 读出数据 = 原始数据 & 新写入的数据
  */
void W25QXX_WritePage(uint32_t address, uint8_t* dataArray, uint16_t count);

/**
  * @brief W25QXX芯片数读据
  * @param address 读出页地址（xxxx00~xxxxFF）
  * @param dataArray 读出数据数组
  * @param count 读出数据数量（无数量限制）
  * @return 无
  */
void W25QXX_ReadPage(uint32_t address, uint8_t* dataArray, uint32_t count);

/**
  * @brief W25QXX芯片擦除扇区(4KB)
  * @param address 扇区地址（xxx000~xxxFFF）
  * @return 无
	* 注：擦除数据后所有数据为0xFF
  */
void W25QXX_SectorErase(uint32_t address);

/**
  * @brief W25QXX芯片擦除块(64KB)
  * @param address 块地址（xx0000~xxFFFF）
  * @return 无
  */
void W25QXX_BlockErase(uint32_t address);

#endif
