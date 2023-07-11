#include "USART2.h"

uint8_t USART2_RxData;
uint8_t USART2_RxFlag;
uint8_t USART2_RxPacket[USART2_DataPackage_Length];
char USART2_DataString[USART2_DataPackage_Length] = "hello";

uint32_t USART2_Pow(uint32_t X, uint32_t Y) {
	uint32_t Result = 1;
	while (Y --) {
		Result *= X;
	}
	return Result;
}


void USART2_Init(void) {
	/* 开启时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* 配置TX引脚 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* 配置RX引脚 */	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* 配置USART */
	USART_InitTypeDef USART_InitStruture;
	USART_InitStruture.USART_BaudRate = USART2_BaudRate;
	USART_InitStruture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruture.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruture.USART_Parity = USART2_Parity;
	USART_InitStruture.USART_StopBits = USART2_StopBits;
	USART_InitStruture.USART_WordLength = USART2_DataLength;
	USART_Init(USART2, &USART_InitStruture);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	/* 配置中断 */
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART2, ENABLE);
}

void USART2_SendByte(uint8_t Byte) {
	USART_SendData(USART2, Byte);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

void USART2_SendArray(uint8_t *Array, uint16_t Length) {
	uint16_t i;
	for (i = 0; i < Length; i ++) {
		USART2_SendByte(Array[i]);
	}
}

void USART2_SendString(char *String) {
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++) {
		USART2_SendByte(String[i]);
	}
}

void USART2_SendNumber(uint32_t Number, uint8_t Length) {
	uint8_t i;
	for (i = 0; i < Length; i ++) {
		USART2_SendByte(Number / USART2_Pow(10, Length - i - 1) % 10 + '0');
	}
}

uint8_t USART2_GetRxFlag(void) {
	if (USART2_RxFlag == 1) {
		USART2_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t USART2_GetRxData(void) {
	return USART2_RxData;
}



void USART2_SendDatePackage_HEX(uint8_t* dataArray, uint16_t dataLength) {
	USART2_SendByte(USART2_DataPackageHead_HEX);
	USART2_SendArray(dataArray, dataLength);
	USART2_SendByte(USART2_DataPackageTial_HEX);
}

void USART2_SendDatePackage_TEXT(char* String) {
	USART2_SendByte(USART2_DataPackageHead_TEXT);
	USART2_SendString(String);
	USART2_SendByte('\r');
	USART2_SendByte('\n');
}


/**
  * @brief 串口中断处理函数
  * @return 无
  */
void USART2_IRQHandler(void) {
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
		USART2_RxData = USART_ReceiveData(USART2);
		USART2_RxFlag = 1;
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}

/**
	* @brief  串口中断处理函数(接收十六进制数据包)
	* @return 无
	*/
//void USART2_IRQHandler(void) {
//	static uint8_t RxState = 0;
//	static uint8_t pRxPacket = 0;
//	
//	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
//		uint8_t RxData = USART_ReceiveData(USART2);
//		
//		if (RxState == 0) {
//				if (RxData == USART2_DataPackageHead_HEX) {  // 接收到包头
//						RxState = 1;
//						pRxPacket = 1;
//				}
//		}
//		else if (RxState == 1) {
//			USART2_RxPacket[0] = RxData;
//			RxState = 2;
//		}
//		else if (RxState == 2) {
//				USART2_RxPacket[pRxPacket] = RxData;
//				pRxPacket++;
//				if (pRxPacket > USART2_RxPacket[0]) {  // 接收到四个数据
//						RxState = 3;
//				}
//		}
//		else if (RxState == 3) {
//				if (RxData == USART2_DataPackageTial_HEX) {  // 接收到包尾
//						RxState = 0;
//						USART2_RxFlag = 1;
//				}
//		}
//		USART_ClearITPendingBit(USART2, USART_IT_RXNE);			
//	}
//}

/**
	* @brief  串口中断处理函数(接收文本数据包)
	* @return 无
	*/
//void USART2_IRQHandler(void) {
//	static uint8_t RxState = 0;
//	static uint8_t pRxPacket = 0;
//	
//	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
//		char RxData = (char) USART_ReceiveData(USART2);
//		
//		if (RxState == 0) {
//			if (USART2_RxFlag == 0 && RxData == USART2_DataPackageHead_TEXT) {  // 接收到包头，防止上一个数据包还没接收全
//				RxState = 1;
//				pRxPacket = 0;
//			}
//		}
//		else if (RxState == 1) {
//			if (RxData == '\r') {  // 接收到包尾
//				RxState = 2;
//			} else {
//				USART2_DataString[pRxPacket] = RxData;
//				pRxPacket++;
//			}
//		}
//		else if (RxState == 2) {
//			if (RxData == '\n') {  // 接收到包尾
//				RxState = 0;
//				USART2_RxFlag = 1;
//				USART2_DataString[pRxPacket] = '\0';  // 给字符串末尾加\0结束
//			}
//		}
//		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//	}
//}
