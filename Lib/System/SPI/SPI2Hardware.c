#include "SPI2Hardware.h"

void  SPI2_Hardware_Init(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	SPI_InitTypeDef	SPI_InitStructure;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		// SPI主机
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// 双线全双工
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		// 数据帧为8Bit
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	// 为高位先行
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;	// 分频系数为128（当前速度为36M/128,分屏越小速度越快）
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		// 空闲状态时钟为第电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	// 第一个边沿开始采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			// 软件模拟NSS
	SPI_InitStructure.SPI_CRCPolynomial = 7;			// CRC的计算数
	SPI_Init(SPI2, &SPI_InitStructure);
	
	SPI_Cmd(SPI2, ENABLE);
}

uint8_t SPI2_Hardware_SwapByte(uint8_t SendByte) {
	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != SET);
	
	SPI_I2S_SendData(SPI2, SendByte);
	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) != SET);
	
	return SPI_I2S_ReceiveData(SPI2);
}
