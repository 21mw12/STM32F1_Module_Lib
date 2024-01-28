#ifndef __I2C_SOFTWARE_H
#define __I2C_SOFTWARE_H

#include "stm32f10x.h"
#include "delay.h"

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����ģ��I2C�Ļ�������
// �汾��V2.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/01/28
//
///////////////////////////////////////////////////////////

/* ���I2C�˿���Ϣ */
#define I2C_Software_GPIOPeriph		RCC_APB2Periph_GPIOB
#define I2C_Software_Port					GPIOB
#define I2C_Software_Pin_SCL			GPIO_Pin_10
#define I2C_Software_Pin_SDA			GPIO_Pin_11

/**
  * @brief ���I2C��ʼ��
  * @return ��
  */
void I2C_Software_Init(void);

/**
  * @brief  I2C��ʼ
  * @param  GPIOx �� IO�˿���
  * @param  GPIO_Pin �� IO�˿�
  * @retval ��
  */
void I2C_Software_StartSignal(void);

/**
  * @brief  I2Cֹͣ
  * @param  GPIOx �� IO�˿���
  * @param  GPIO_Pin �� IO�˿�
  * @retval ��
  */
void I2C_Software_StopSignal(void);

/**
  * @brief  I2C����һ���ֽ�
  * @param  Byte Ҫ���͵�һ���ֽ�
  * @retval ��
  */
void I2C_Software_SendData(uint8_t Byte);

/**
  * @brief  I2C����һ���ֽ�
  * @retval ���յ�������
  */
uint8_t I2C_Software_ReceiveByte(void);

/**
  * @brief  ����Ӧ��
  * @param  Ӧ����Ϣ
  * @retval ��
  */
void I2C_Software_SendAck(uint8_t AckBit);

/**
  * @brief  ����Ӧ��
  * @retval Ӧ����Ϣ
  */
uint8_t I2C_Software_ReceiveAck(void);

/*************************************************************************/

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


///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/07/07
//				ʵ�������ģ��I2C�Ļ�������
// V2.0: 2024/01/28
//				����Ӳ��I2C������ʱ�����
//
///////////////////////////////////////////////////////////
