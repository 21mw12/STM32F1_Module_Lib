#ifndef __SPI2_HARDWARE_H
#define __SPI2_HARDWARE_H

#include "stm32f10x.h"
#include "delay.h"

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�Ӳ��SPI2�Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/12/27
//
// ע���ڽ�Э�Ƽ��Ĵ����������ͨ���Ե��޸�
//
///////////////////////////////////////////////////////////

/**
  * @brief Ӳ��SPI2��ʼ��
  * @return ��
  */
void SPI2_Hardware_Init(void);

/**
  * @brief SPI2����һ���ֽڣ�ģʽ0��
  * @param SendByte Ҫ���͵�����
  * @return ���յ�������
  */
uint8_t SPI2_Hardware_SwapByte(uint8_t SendByte);

#endif
