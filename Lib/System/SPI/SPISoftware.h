#ifndef __SPI_SOFTWARE_H
#define __SPI_SOFTWARE_H

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

#include "stm32f10x.h"

/* ���SPI�˿���Ϣ */
#define SPI_Software_GPIOPeriph		RCC_APB2Periph_GPIOA
#define SPI_Software_Port					GPIOA
#define SPI_Software_Pin_CLK			GPIO_Pin_5
#define SPI_Software_Pin_MISO			GPIO_Pin_6
#define SPI_Software_Pin_MOSI			GPIO_Pin_7

/**
  * @brief ���SPI��ʼ��
  * @return ��
  */
void SPI_Software_Init(void);

/**
  * @brief SPI����һ���ֽڣ�ģʽ0��
  * @param SendByte Ҫ���͵�����
  * @return ���յ�������
  */
uint8_t SPI_Software_SwapByte(uint8_t SendByte);

#endif
