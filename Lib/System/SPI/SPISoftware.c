#include "SPISoftware.h"

///////////////////////////////////////////////////////////
//
// SPI����ʱ��ʵ��
//
///////////////////////////////////////////////////////////

/**
  * @brief  CLKд����
  * @param  state �� ��������
  * @retval ��
  */
void SPI_CLK_Write(uint8_t state) {
	GPIO_WriteBit(SPI_Software_PORT, SPI_Software_CLK_PIN, (BitAction)state);
}

/**
  * @brief  MOSIд����
  * @param  state �� ��������
  * @retval ��
  */
void SPI_MOSI_Write(uint8_t state) {
	GPIO_WriteBit(SPI_Software_PORT, SPI_Software_MOSI_PIN, (BitAction)state);
}

/**
  * @brief  SDA������
  * @retval ��ȡ��������
  */
uint8_t SPI_MISO_Read(void) {
	return GPIO_ReadInputDataBit(SPI_Software_PORT, SPI_Software_MISO_PIN);
}

///////////////////////////////////////////////////////////
//
// SPI��������ʵ��
//
///////////////////////////////////////////////////////////

void SPI_Software_Init(void) {
  RCC_APB2PeriphClockCmd(SPI_Software_GPIOPeriph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SPI_Software_CLK_PIN | SPI_Software_MOSI_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(SPI_Software_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI_Software_MISO_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(SPI_Software_PORT, &GPIO_InitStructure);
	
	SPI_CLK_Write(0);
}

uint8_t SPI_Software_SwapByte(uint8_t SendByte) {	
	for (uint8_t i = 0; i < 8; i++) {
		SPI_MOSI_Write(SendByte & 0x80);
		SendByte <<= 1;
		SPI_CLK_Write(1);
		if (SPI_MISO_Read() == 1) {
			SendByte |= 0x01;
		}
		SPI_CLK_Write(0);
	}
	
	return SendByte;
}
