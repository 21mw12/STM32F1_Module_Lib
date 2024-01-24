#include "SPISoftware.h"
#include "Delay.h"

/**
  * @brief  CLK写数据
  * @param  state ： 数据内容
  * @retval 无
  */
void SPI_CLK_Write(uint8_t state) {
	GPIO_WriteBit(SPI_Software_Port, SPI_Software_Pin_CLK, (BitAction)state);
}

/**
  * @brief  MOSI写数据
  * @param  state ： 数据内容
  * @retval 无
  */
void SPI_MOSI_Write(uint8_t state) {
	GPIO_WriteBit(SPI_Software_Port, SPI_Software_Pin_MOSI, (BitAction)state);
}

/**
  * @brief  SDA读数据
  * @retval 读取到的数据
  */
uint8_t SPI_MISO_Read(void) {
	return GPIO_ReadInputDataBit(SPI_Software_Port, SPI_Software_Pin_MISO);
}

void SPI_Software_Init(void) {
  RCC_APB2PeriphClockCmd(SPI_Software_GPIOPeriph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SPI_Software_Pin_CLK | SPI_Software_Pin_MOSI;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(SPI_Software_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI_Software_Pin_MISO;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(SPI_Software_Port, &GPIO_InitStructure);
	
	SPI_CLK_Write(1);
}

uint8_t SPI_Software_SwapByte(uint8_t SendByte) {	
	for (uint8_t i = 0; i < 8; i++) {
		SPI_MOSI_Write(SendByte & 0x80);
		SendByte <<= 1;
		SPI_CLK_Write(0);
		if (SPI_MISO_Read() == 1) {
			SendByte |= 0x01;
		}
		SPI_CLK_Write(1);
	}
	
	return SendByte;
}
