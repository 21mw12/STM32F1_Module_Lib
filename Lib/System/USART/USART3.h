#ifndef __USART3_H
#define __USART3_H

///////////////////////////////////////////////////////////
//
// 文件功能：串口2的相基础功能
// 版本：V1.2
// 作者：墨蔚（MW）
// 修改时间：2023/07/11
//
// 对应引脚：           	 TX        RX
//         		USART3		 P9			   PA10
//         		USART3     PA2       PA3
//         		USART3     PB10      PB11
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

/* USART配置 */
#define USART3_BaudRate			115200									// 波特率
#define USART3_Parity				USART_Parity_No					// 校验方式
#define USART3_StopBits			USART_StopBits_1				// 停止位长度
#define USART3_DataLength		USART_WordLength_8b			// 数据长度

/* USART数据包相关配置 */
/* 注意!!!: 要在USART3.c文件的最下面释放和屏蔽相对应的串口中断函数 */
#define USART3_DataPackage_Length			10				// 数据包最大长度
#define USART3_DataPackageHead_HEX		0xFF			// 十六进制数据包的包头
#define USART3_DataPackageTial_HEX		0x00			// 十六进制数据包的包尾
#define USART3_DataPackageHead_TEXT		'@'				// 文本数据包的包头  （包尾默认为Windows平台的换行符“\r\n”）

/* 串口接收数据 */
extern uint8_t USART3_RxData;
/**
	*  Serial_RxPacket数组（十六进制数据包数组）解释：
	*  数组的第一位(下标0)表示有效数据量， 第二位(下标1)开始才是真正的数据
	*/
extern uint8_t USART3_RxPacket[USART3_DataPackage_Length];
/* Serial_DataString数组（文本数据包数组） */
extern char USART3_DataString[USART3_DataPackage_Length];


/**
  * @brief 串口初始化
  * @return 无
  */
void USART3_Init(void);

/**
  * @brief 串口发送一个字节
  * @param Byte	要发送的数据
  * @return 无
  */
void USART3_SendByte(uint8_t Byte);

/**
  * @brief 串口发送数组
  * @param Array	要发送的数组
  * @param Length	数组的长度 / 要发送的长度
  * @return 无
  */
void USART3_SendArray(uint8_t* Array, uint16_t Length);

/**
  * @brief 串口发送字符串
  * @param String	要发送的数组
  * @return 无
  */
void USART3_SendString(char* String);

/**
  * @brief 串口发送数字
  * @param Number	要发送的数字
  * @param Length	数字的长度
  * @return 无
  */
void USART3_SendNumber(uint32_t Number, uint8_t Length);

/**
  * @brief 获得接收标志位
  * @return 是否有接收到数据		0：没有
	* 													1：有
  */
uint8_t USART3_GetRxFlag(void);

/**
  * @brief 获得接收到的数据
  * @return 接收到的数据
  */
uint8_t USART3_GetRxData(void);

/**
  * @brief 发送十六进制数据包
  * @param dataArray 数据数组
  * @param dataLength 数据长度
  * @return 无
  */
void USART3_SendDatePackage_HEX(uint8_t* dataArray, uint16_t dataLength);

/**
  * @brief 发送文本数据包
  * @param String	文本内容
  * @return 无
  */
void USART3_SendDatePackage_TEXT(char* String);

#endif
