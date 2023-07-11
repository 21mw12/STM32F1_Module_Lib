#include "USART1.h"

uint8_t USART1_RxData;
uint8_t USART1_RxFlag;
uint8_t USART1_RxPacket[USART1_DataPackage_Length];
char USART1_DataString[USART1_DataPackage_Length] = "hello";

uint32_t USART1_Pow(uint32_t X, uint32_t Y) {
	uint32_t Result = 1;
	while (Y --) {
		Result *= X;
	}
	return Result;
}


int fputc(int ch, FILE *f) {
	USART1_SendByte(ch);
	return ch;
}

void USART1_Init(void) {
	/* 开启时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* 配置TX引脚 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* 配置RX引脚 */	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* 配置USART */
	USART_InitTypeDef USART_InitStruture;
	USART_InitStruture.USART_BaudRate = USART1_BaudRate;
	USART_InitStruture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruture.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruture.USART_Parity = USART1_Parity;
	USART_InitStruture.USART_StopBits = USART1_StopBits;
	USART_InitStruture.USART_WordLength = USART1_DataLength;
	USART_Init(USART1, &USART_InitStruture);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	/* 配置中断 */
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}

void USART1_SendByte(uint8_t Byte) {
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void USART1_SendArray(uint8_t *Array, uint16_t Length) {
	uint16_t i;
	for (i = 0; i < Length; i ++) {
		USART1_SendByte(Array[i]);
	}
}

void USART1_SendString(char *String) {
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++) {
		USART1_SendByte(String[i]);
	}
}

void USART1_SendNumber(uint32_t Number, uint8_t Length) {
	uint8_t i;
	for (i = 0; i < Length; i ++) {
		USART1_SendByte(Number / USART1_Pow(10, Length - i - 1) % 10 + '0');
	}
}

void USART1_printf(char *format, ...) {
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	USART1_SendString(String);
}

uint8_t USART1_GetRxFlag(void) {
	if (USART1_RxFlag == 1) {
		USART1_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t USART1_GetRxData(void) {
	return USART1_RxData;
}



void USART1_SendDatePackage_HEX(uint8_t* dataArray, uint16_t dataLength) {
	USART1_SendByte(USART1_DataPackageHead_HEX);
	USART1_SendArray(dataArray, dataLength);
	USART1_SendByte(USART1_DataPackageTial_HEX);
}

void USART1_SendDatePackage_TEXT(char* String) {
	USART1_SendByte(USART1_DataPackageHead_TEXT);
	USART1_SendString(String);
	USART1_SendByte('\r');
	USART1_SendByte('\n');
}


/**
  * @brief 串口中断处理函数
  * @return 无
  */
void USART1_IRQHandler(void) {
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
		USART1_RxData = USART_ReceiveData(USART1);
		USART1_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

/**
	* @brief  串口中断处理函数(接收十六进制数据包)
	* @return 无
	*/
//void USART1_IRQHandler(void) {
//	static uint8_t RxState = 0;
//	static uint8_t pRxPacket = 0;
//	
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
//		uint8_t RxData = USART_ReceiveData(USART1);
//		
//		if (RxState == 0) {
//				if (RxData == USART1_DataPackageHead_HEX) {  // 接收到包头
//						RxState = 1;
//						pRxPacket = 1;
//				}
//		}
//		else if (RxState == 1) {
//			USART1_RxPacket[0] = RxData;
//			RxState = 2;
//		}
//		else if (RxState == 2) {
//				USART1_RxPacket[pRxPacket] = RxData;
//				pRxPacket++;
//				if (pRxPacket > USART1_RxPacket[0]) {  // 接收到四个数据
//						RxState = 3;
//				}
//		}
//		else if (RxState == 3) {
//				if (RxData == USART1_DataPackageTial_HEX) {  // 接收到包尾
//						RxState = 0;
//						USART1_RxFlag = 1;
//				}
//		}
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			
//	}
//}

/**
	* @brief  串口中断处理函数(接收文本数据包)
	* @return 无
	*/
//void USART1_IRQHandler(void) {
//	static uint8_t RxState = 0;
//	static uint8_t pRxPacket = 0;
//	
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
//		char RxData = (char) USART_ReceiveData(USART1);
//		
//		if (RxState == 0) {
//			if (USART1_RxFlag == 0 && RxData == USART1_DataPackageHead_TEXT) {  // 接收到包头，防止上一个数据包还没接收全
//				RxState = 1;
//				pRxPacket = 0;
//			}
//		}
//		else if (RxState == 1) {
//			if (RxData == '\r') {  // 接收到包尾
//				RxState = 2;
//			} else {
//				USART1_DataString[pRxPacket] = RxData;
//				pRxPacket++;
//			}
//		}
//		else if (RxState == 2) {
//			if (RxData == '\n') {  // 接收到包尾
//				RxState = 0;
//				USART1_RxFlag = 1;
//				USART1_DataString[pRxPacket] = '\0';  // 给字符串末尾加\0结束
//			}
//		}
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	}
//}
