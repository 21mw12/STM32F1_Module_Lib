#ifndef __STM32F10x_I2C_H
#define __STM32F10x_I2C_H

#include "stm32f10x.h"

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�I2C�Ļ�������
// �汾��V1.1
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/07
//
///////////////////////////////////////////////////////////

// ѡ�����I2C����Ӳ��I2C
// 			0: ���I2C
// 			1: Ӳ��I2C
#define SoftOrHaradWareI2C		1

/**
  * @brief I2C���߳�ʼ��
  * @return ��
  */
void I2C_Bus_Init(void);

/**
  * @brief I2C����һ���ֽ�
  * @param address �ӻ���ַ
  * @param command ָ��
  * @param data ����
  * @return ��
  */
void I2C_Bus_SendByte(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t pBuffer);

/**
  * @brief I2C����һ������
  * @param address �ӻ���ַ
  * @param command ָ��
  * @param array ��������
  * @param length ���ݳ��ȣ�����������
  * @return ��
  */
void I2C_Bus_SendArray(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t* pBuffer, uint16_t NumByteToWrite);

/**
  * @brief I2C����һ���ֽ�
  * @param address �ӻ���ַ
  * @param reg ��ȡ�Ĵ���
  * @return ��ȡ��������
  */
uint8_t I2C_Bus_ReadByte(uint8_t SlaveAddr, uint8_t readAddr);

/**
  * @brief I2C����һ������
  * @param address �ӻ���ַ
  * @param reg ��ȡ�Ĵ���
  * @param array ��������
  * @param length ���ݳ��ȣ�����������
  * @return ��
  */
uint8_t I2C_Bus_ReadArray(uint8_t SlaveAddr, uint8_t readAddr, uint8_t* pBuffer, uint16_t NumByteToRead);

#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/04/21
//				ʵ�������I2C�Ļ�������
// V1.1: 2023/07/07
//				ʵ������Ӳ��I2C�Ļ������ܲ����Լ򵥵��л�
//
///////////////////////////////////////////////////////////
