#include "USART3.h"
#include <stdio.h>
#include <stdarg.h>

uint8_t USART3_RxData;
uint8_t USART3_RxFlag;
uint8_t USART3_RxPacket[USART3_DataPackage_Length];
char USART3_DataString[USART3_DataPackage_Length] = "hello";

uint32_t USART3_Pow(uint32_t X, uint32_t Y) {
	uint32_t Result = 1;
	while (Y --) {
		Result *= X;
	}
	return Result;
}


void USART3_Init(void) {
	/* 开启时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* 配置TX引脚 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* 配置RX引脚 */	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* 配置USART */
	USART_InitTypeDef USART_InitStruture;
	USART_InitStruture.USART_BaudRate = USART3_BaudRate;
	USART_InitStruture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruture.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruture.USART_Parity = USART3_Parity;
	USART_InitStruture.USART_StopBits = USART3_StopBits;
	USART_InitStruture.USART_WordLength = USART3_DataLength;
	USART_Init(USART3, &USART_InitStruture);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	/* 配置中断 */
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART3, ENABLE);
}

void USART3_SendByte(uint8_t Byte) {
	USART_SendData(USART3, Byte);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

void USART3_SendArray(uint8_t *Array, uint16_t Length) {
	uint16_t i;
	for (i = 0; i < Length; i ++) {
		USART3_SendByte(Array[i]);
	}
}

void USART3_SendString(char *String) {
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++) {
		USART3_SendByte(String[i]);
	}
}

void USART3_SendNumber(uint32_t Number, uint8_t Length) {
	uint8_t i;
	for (i = 0; i < Length; i ++) {
		USART3_SendByte(Number / USART3_Pow(10, Length - i - 1) % 10 + '0');
	}
}

uint8_t USART3_GetRxFlag(void) {
	if (USART3_RxFlag == 1) {
		USART3_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t USART3_GetRxData(void) {
	return USART3_RxData;
}



void USART3_SendDatePackage_HEX(uint8_t* dataArray, uint16_t dataLength) {
	USART3_SendByte(USART3_DataPackageHead_HEX);
	USART3_SendArray(dataArray, dataLength);
	USART3_SendByte(USART3_DataPackageTial_HEX);
}

void USART3_SendDatePackage_TEXT(char* String) {
	USART3_SendByte(USART3_DataPackageHead_TEXT);
	USART3_SendString(String);
	USART3_SendByte('\r');
	USART3_SendByte('\n');
}


/**
  * @brief 串口中断处理函数
  * @return 无
  */
void USART3_IRQHandler(void) {
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET) {
		USART3_RxData = USART_ReceiveData(USART3);
		USART3_RxFlag = 1;
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}
}

/**
	* @brief  串口中断处理函数(接收十六进制数据包)
	* @return 无
	*/
//void USART3_IRQHandler(void) {
//	static uint8_t RxState = 0;
//	static uint8_t pRxPacket = 0;
//	
//	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET) {
//		uint8_t RxData = USART_ReceiveData(USART3);
//		
//		if (RxState == 0) {
//				if (RxData == USART3_DataPackageHead_HEX) {  // 接收到包头
//						RxState = 1;
//						pRxPacket = 1;
//				}
//		}
//		else if (RxState == 1) {
//			USART3_RxPacket[0] = RxData;
//			RxState = 2;
//		}
//		else if (RxState == 2) {
//				USART3_RxPacket[pRxPacket] = RxData;
//				pRxPacket++;
//				if (pRxPacket > USART3_RxPacket[0]) {  // 接收到四个数据
//						RxState = 3;
//				}
//		}
//		else if (RxState == 3) {
//				if (RxData == USART3_DataPackageTial_HEX) {  // 接收到包尾
//						RxState = 0;
//						USART3_RxFlag = 1;
//				}
//		}
//		USART_ClearITPendingBit(USART3, USART_IT_RXNE);			
//	}
//}

/**
	* @brief  串口中断处理函数(接收文本数据包)
	* @return 无
	*/
//void USART3_IRQHandler(void) {
//	static uint8_t RxState = 0;
//	static uint8_t pRxPacket = 0;
//	
//	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET) {
//		char RxData = (char) USART_ReceiveData(USART3);
//		
//		if (RxState == 0) {
//			if (USART3_RxFlag == 0 && RxData == USART3_DataPackageHead_TEXT) {  // 接收到包头，防止上一个数据包还没接收全
//				RxState = 1;
//				pRxPacket = 0;
//			}
//		}
//		else if (RxState == 1) {
//			if (RxData == '\r') {  // 接收到包尾
//				RxState = 2;
//			} else {
//				USART3_DataString[pRxPacket] = RxData;
//				pRxPacket++;
//			}
//		}
//		else if (RxState == 2) {
//			if (RxData == '\n') {  // 接收到包尾
//				RxState = 0;
//				USART3_RxFlag = 1;
//				USART3_DataString[pRxPacket] = '\0';  // 给字符串末尾加\0结束
//			}
//		}
//		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
//	}
//}
