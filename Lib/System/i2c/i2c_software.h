#ifndef __STM32F10x_I2C_SOFTWARE_H
#define __STM32F10x_I2C_SOFTWARE_H

#include "stm32f10x.h"
#include "delay.h"

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����ģ��I2C�Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/07
//
///////////////////////////////////////////////////////////

/* ���I2C�˿���Ϣ */
#define I2C_Software_GPIOPeriph		RCC_APB2Periph_GPIOB
#define I2C_Software_PORT					GPIOB
#define I2C_Software_SCL_PIN			GPIO_Pin_8
#define I2C_Software_SDA_PIN			GPIO_Pin_9

/**
  * @brief ���I2C��ʼ��
  * @return ��
  */
void I2C_Software_Init(void);

/**
  * @brief ���I2C����һ���ֽ�
  * @param address �ӻ���ַ
  * @param command ָ��
  * @param data ����
  * @return ��
  */
void I2C_Software_SendByte(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t pBuffer);

/**
  * @brief ���I2C����һ������
  * @param address �ӻ���ַ
  * @param command ָ��
  * @param array ��������
  * @param length ���ݳ��ȣ�����������
  * @return ��
  */
void I2C_Software_SendArray(uint8_t SlaveAddr, uint8_t WriteAddr, uint8_t* pBuffer, u16 NumByteToWrite);

/**
  * @brief ���I2C��һ���ֽ�
  * @param address �ӻ���ַ
  * @param reg ��ַ
  * @return ��ȡ��������
  */
uint8_t I2C_Software_ReadByte(uint8_t SlaveAddr, uint8_t readAddr);

/**
  * @brief ���I2C��һ������
  * @param address �ӻ���ַ
  * @param reg ��ַ
  * @param array ��������
  * @param length ���ݳ��ȣ�����������
  * @return ��
  */
void I2C_Software_ReadArray(uint8_t SlaveAddr, uint8_t readAddr, uint8_t* pBuffer, u16 NumByteToRead);

#endif
