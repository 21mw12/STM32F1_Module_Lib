#ifndef __SERIAL_H
#define __SERIAL_H

///////////////////////////////////////////////////////////
//
// 文件功能：串口的相基础功能
// 版本：V1.1
// 作者：墨蔚（MW）
// 修改时间：2023/06/13
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

/* USART端口配置 */
#define USART_Number		USART1
#define USART_Port			GPIOA
#define USART_Pin_RX		GPIO_Pin_9
#define USART_Pin_TX		GPIO_Pin_10
#define USART_Periph				RCC_APB2Periph_USART1
#define USART_PortPeriph		RCC_APB2Periph_GPIOA

/* USART配置 */
#define BaudRate		115200									// 波特率
#define Parity			USART_Parity_No					// 校验方式
#define StopBits		USART_StopBits_1				// 停止位长度
#define DataLength		USART_WordLength_8b		// 数据长度

/* USART数据包相关配置（注意释放和屏蔽相对应的串口中断函数） */
#define DataPackage_Length		10				// 数据包最大长度
#define DataPackageHead_HEX		0xFF		// 十六进制数据包的包头
#define DataPackageTial_HEX		0x00		// 十六进制数据包的包尾
#define DataPackageHead_TEXT	'@'			// 文本数据包的包头  （包尾默认为Windows平台的换行符“\r\n”）

/**
  * @brief 串口初始化
  * @return 无
  */
void Serial_Init(void);

/**
  * @brief 串口发送一个字节
  * @param Byte	要发送的数据
  * @return 无
  */
void Serial_SendByte(uint8_t Byte);

/**
  * @brief 串口发送数组
  * @param Array	要发送的数组
  * @param Length	数组的长度 / 要发送的长度
  * @return 无
  */
void Serial_SendArray(uint8_t* Array, uint16_t Length);

/**
  * @brief 串口发送字符串
  * @param String	要发送的数组
  * @return 无
  */
void Serial_SendString(char* String);

/**
  * @brief 串口发送数字
  * @param Number	要发送的数字
  * @param Length	数字的长度
  * @return 无
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length);

/**
  * @brief 格式化输出（标准C的printf语句）
  * @return 无
  */
void Serial_printf(char *format, ...);

/**
  * @brief 获得接收标志位
  * @return 是否有接收到数据		0：没有
	* 													1：有
  */
uint8_t Serial_GetRxFlag(void);

/**
  * @brief 获得接收到的数据
  * @return 接收到的数据
  */
uint8_t Serial_GetRxData(void);

/**
  * @brief 发送十六进制数据包
  * @param dataArray 数据数组
  * @param dataLength 数据长度
  * @return 无
  */
void Serial_SendDatePackage_HEX(uint8_t* dataArray, uint16_t dataLength);

/**
  * @brief 发送文本数据包
  * @param String	文本内容
  * @return 无
  */
void Serial_SendDatePackage_TEXT(char* String);

#endif


///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/06/11
//				实现了基础的串口接收发送功能
// V1.1: 2023/06/13
//				实现了串口发送接收不定长数据包，
// 				包括十六进制数据包和文本数据包
//
///////////////////////////////////////////////////////////
