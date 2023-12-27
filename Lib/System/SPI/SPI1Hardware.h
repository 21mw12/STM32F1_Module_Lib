#ifndef __SPI1_HARDWARE_H
#define __SPI1_HARDWARE_H

#include "stm32f10x.h"
#include "delay.h"

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�Ӳ��SPI1�Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/12/27
//
// ע���ڽ�Э�Ƽ��Ĵ����������ͨ���Ե��޸�
//
///////////////////////////////////////////////////////////

/**
  * @brief Ӳ��SPI1��ʼ��
  * @return ��
  */
void SPI1_Hardware_Init(void);

/**
  * @brief SPI1����һ���ֽڣ�ģʽ0��
  * @param SendByte Ҫ���͵�����
  * @return ���յ�������
  */
uint8_t SPI1_Hardware_SwapByte(uint8_t SendByte);

#endif
