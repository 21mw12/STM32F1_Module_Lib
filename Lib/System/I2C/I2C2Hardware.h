#ifndef __I2C2_HARDWARE_H
#define __I2C2_HARDWARE_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�Ӳ��I2C�Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/07
//
// ��Ӧ���ţ�                SCL                 SDA
//            I2C1    PB6 / PB8(��ӳ��)    PB7 / PB9(��ӳ��)
//            I2C2          PB10                PB11
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* Ӳ��I2C������Ϣ */
#define I2C2_HostAddress						0xFC				// ����I2C�ĵ�ַ�����úʹӻ���ַ�ظ���
#define I2C2_Speed									50000			// I2C�����ٶȣ�I2C���ܲ����õ�ʱ���ʵ������ò�����
#define I2C2_Timeout								10000				//�������������ĳ�ʼֵ

/**
  * @brief Ӳ��I2C��ʼ��
  * @return ��
  */
void I2C2_Hardware_Init(void);

/**
  * @brief Ӳ��I2C����һ���ֽ�
  * @param address �ӻ���ַ
  * @param command ָ��
  * @param data ����
  * @return ��
  */
void I2C2_Hardware_SendByte(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t pBuffer);

/**
  * @brief Ӳ��I2C����һ������
  * @param address �ӻ���ַ
  * @param command ָ��
  * @param array ��������
  * @param length ���ݳ��ȣ�����������
  * @return ��
  */
void I2C2_Hardware_SendArray(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t* pBuffer, u16 NumByteToWrite);

/**
  * @brief Ӳ��I2C����һ���ֽ�
  * @param address �ӻ���ַ
  * @param reg ��ȡ�Ĵ���
  * @return ��ȡ��������
  */
uint8_t I2C2_Hardware_ReadByte(uint8_t SlaveAddr, uint8_t readAddr);

/**
  * @brief Ӳ��I2C����һ������
  * @param address �ӻ���ַ
  * @param reg ��ȡ�Ĵ���
  * @param array ��������
  * @param length ���ݳ��ȣ�����������
  * @return ��
  */
uint8_t I2C2_Hardware_ReadArray(uint8_t SlaveAddr, uint8_t readAddr, uint8_t* pBuffer, u16 NumByteToRead);

#endif
