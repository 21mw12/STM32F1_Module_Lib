#include "usart.h"

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

/**
	*  Serial_RxPacket������ͣ�
	*  1.������ݰ���usart.h������
	*  2.����ĵ�һλ(�±�0)��ʾ��Ч�������� �ڶ�λ(�±�1)��ʼ��������������
	*/
uint8_t Serial_RxPacket[DataPackage_Length];
char Serial_DataString[DataPackage_Length] = "hello";

uint32_t Serial_Pow(uint32_t X, uint32_t Y) {
	uint32_t Result = 1;
	while (Y --) {
		Result *= X;
	}
	return Result;
}


int fputc(int ch, FILE *f) {
	Serial_SendByte(ch);
	return ch;
}

void Serial_Init(void) {
	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(USART_Periph, ENABLE);
	RCC_APB2PeriphClockCmd(USART_PortPeriph, ENABLE);
	
	/* ����RX���� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = USART_Pin_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_Port, &GPIO_InitStructure);
	
	/* ����TX���� */	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = USART_Pin_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_Port, &GPIO_InitStructure);
	
	/* ����USART */
	USART_InitTypeDef USART_InitStruture;
	USART_InitStruture.USART_BaudRate = BaudRate;
	USART_InitStruture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruture.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruture.USART_Parity = Parity;
	USART_InitStruture.USART_StopBits = StopBits;
	USART_InitStruture.USART_WordLength = DataLength;
	USART_Init(USART_Number, &USART_InitStruture);
	
	USART_ITConfig(USART_Number, USART_IT_RXNE, ENABLE);
	
	/* �����ж� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART_Number, ENABLE);
}

void Serial_SendByte(uint8_t Byte) {
	USART_SendData(USART_Number, Byte);
	while (USART_GetFlagStatus(USART_Number, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length) {
	uint16_t i;
	for (i = 0; i < Length; i ++) {
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String) {
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++) {
		Serial_SendByte(String[i]);
	}
}

void Serial_SendNumber(uint32_t Number, uint8_t Length) {
	uint8_t i;
	for (i = 0; i < Length; i ++) {
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

void Serial_printf(char *format, ...) {
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

uint8_t Serial_GetRxFlag(void) {
	if (Serial_RxFlag == 1) {
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void) {
	return Serial_RxData;
}



void Serial_SendDatePackage_HEX(uint8_t* dataArray, uint16_t dataLength) {
	Serial_SendByte(DataPackageHead_HEX);
	Serial_SendArray(dataArray, dataLength);
	Serial_SendByte(DataPackageTial_HEX);
}

void Serial_SendDatePackage_TEXT(char* String) {
	Serial_SendByte(DataPackageHead_TEXT);
	Serial_SendString(String);
	Serial_SendByte('\r');
	Serial_SendByte('\n');
}


/**
  * @brief �����жϴ�����
  * @return ��
  */
//void USART1_IRQHandler(void) {
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
//		Serial_RxData = USART_ReceiveData(USART_Number);
//		Serial_RxFlag = 1;
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	}
//}

/**
	* @brief  �����жϴ�����(����ʮ���������ݰ�)
	* @return ��
	*/
//void USART1_IRQHandler(void) {
//	static uint8_t RxState = 0;
//	static uint8_t pRxPacket = 0;
//	
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
//		uint8_t RxData = USART_ReceiveData(USART1);
//		
//		if (RxState == 0) {
//				if (RxData == DataPackageHead_HEX) {  // ���յ���ͷ
//						RxState = 1;
//						pRxPacket = 1;
//				}
//		}
//		else if (RxState == 1) {
//			Serial_RxPacket[0] = RxData;
//			RxState = 2;
//		}
//		else if (RxState == 2) {
//				Serial_RxPacket[pRxPacket] = RxData;
//				pRxPacket++;
//				if (pRxPacket > Serial_RxPacket[0]) {  // ���յ��ĸ�����
//						RxState = 3;
//				}
//		}
//		else if (RxState == 3) {
//				if (RxData == DataPackageTial_HEX) {  // ���յ���β
//						RxState = 0;
//						Serial_RxFlag = 1;
//				}
//		}
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			
//	}
//}

/**
	* @brief  �����жϴ�����(�����ı����ݰ�)
	* @return ��
	*/
void USART1_IRQHandler(void) {
	static uint8_t RxState = 0;
	static uint8_t pRxPacket = 0;
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
		char RxData = (char) USART_ReceiveData(USART1);
		
		if (RxState == 0) {
			if (Serial_RxFlag == 0 && RxData == '@') {  // ���յ���ͷ����ֹ��һ�����ݰ���û����ȫ
				RxState = 1;
				pRxPacket = 0;
			}
		}
		else if (RxState == 1) {
			if (RxData == '\r') {  // ���յ���β
				RxState = 2;
			} else {
				Serial_DataString[pRxPacket] = RxData;
				pRxPacket++;
			}
		}
		else if (RxState == 2) {
			if (RxData == '\n') {  // ���յ���β
				RxState = 0;
				Serial_RxFlag = 1;
				Serial_DataString[pRxPacket] = '\0';  // ���ַ���ĩβ��\0����
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
