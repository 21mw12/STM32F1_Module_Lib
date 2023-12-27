#include "SPI1Hardware.h"

void  SPI1_Hardware_Init(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SPI_InitTypeDef	SPI_InitStructure;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		// SPI����
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// ˫��ȫ˫��
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		// ����֡Ϊ8Bit
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	// Ϊ��λ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;	// ��Ƶϵ��Ϊ128����ǰ�ٶ�Ϊ72M/128,����ԽС�ٶ�Խ�죩
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		// ����״̬ʱ��Ϊ�ڵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	// ��һ�����ؿ�ʼ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			// ���ģ��NSS
	SPI_InitStructure.SPI_CRCPolynomial = 7;			// CRC�ļ�����
	SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_Cmd(SPI1, ENABLE);
}

uint8_t SPI1_Hardware_SwapByte(uint8_t SendByte) {
	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
	
	SPI_I2S_SendData(SPI1, SendByte);
	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET);
	
	return SPI_I2S_ReceiveData(SPI1);
}
