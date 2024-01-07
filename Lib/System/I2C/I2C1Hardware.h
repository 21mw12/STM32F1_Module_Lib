#ifndef __I2C1HARDWARE_H
#define __I2C1HARDWARE_H

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
#define I2C1_HostAddress						0xCF			// ����I2C�ĵ�ַ�����úʹӻ���ַ�ظ���
#define I2C1_Speed									400000		// I2C�����ٶȣ�I2C���ܲ����õ�ʱ���ʵ������ò�����
#define I2C1_Timeout								10000			//�������������ĳ�ʼֵ

/**
  * @brief Ӳ��I2C1��ʼ��
  * @return ��
  */
void I2C1_Hardware_Init(void);

/**
  * @brief Ӳ��I2C1��ʼ�ź�
  * @return ��
  */
void I2C1_Hardware_StartSignal(void);

/**
  * @brief Ӳ��I2C1�����ź�
  * @return ��
  */
void I2C1_Hardware_StopSignal(void);

/**
  * @brief Ӳ��I2C1�����豸д��ַ
  * @param Address �ӻ���ַ
  * @return ��
  */
void I2C1_Hardware_SendWriteAddress(uint8_t Address);

/**
  * @brief Ӳ��I2C1�����豸����ַ
  * @param Address �ӻ���ַ
  * @return ��
  */
void I2C1_Hardware_SendReadAddress(uint8_t Address);

/**
  * @brief Ӳ��I2C1����һ�ֽ�����
  * @param I2CData ���͵�����
  * @return ��
  */
void I2C1_Hardware_SendData(uint8_t Data);

/**
  * @brief Ӳ��I2C1����һ�ֽ�����
  * @return ���յ�������
  */
uint8_t I2C1_Hardware_ReceiveData(void);

/**
  * @brief Ӳ��I2C1�ر�Ӧ���ź�
  * @return ��
  */
void I2C1_Hardware_CloseACKSignal(void);

/**
  * @brief Ӳ��I2C1��Ӧ���ź�
  * @return ��
  */
void I2C1_Hardware_OpenACKSignal(void);

#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/07/07
//				ʵ����Ӳ��IC�Ļ�������
// V2.0: 2024/01/06
//				��I2C�Ĺ���ԭ�ӻ���������븴���Լ����ݸ���ģ��
//
///////////////////////////////////////////////////////////
