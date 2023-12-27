#ifndef __SPI_SOFTWARE_H
#define __SPI_SOFTWARE_H

#include "stm32f10x.h"
#include "delay.h"

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����ģ��SPI�Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/12/27
//
// ע���ڽ�Э�Ƽ��Ĵ����������ͨ���Ե��޸�
//
///////////////////////////////////////////////////////////

/* ���SPI�˿���Ϣ */
#define SPI_Software_GPIOPeriph		RCC_APB2Periph_GPIOA
#define SPI_Software_PORT					GPIOA
#define SPI_Software_CLK_PIN			GPIO_Pin_5
#define SPI_Software_MISO_PIN			GPIO_Pin_6
#define SPI_Software_MOSI_PIN			GPIO_Pin_7

/**
  * @brief ���SPI��ʼ��
  * @return ��
  */
void SPI_Software_Init(void);

/**
  * @brief SPI����һ���ֽڣ�ģʽ0��
  * @param 
  * @return 
  */
uint8_t SPI_Software_SwapByte(uint8_t SendByte);

#endif
