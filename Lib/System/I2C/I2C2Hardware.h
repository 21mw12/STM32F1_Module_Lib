#ifndef __I2C2_HARDWARE_H
#define __I2C2_HARDWARE_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�Ӳ��I2C�Ļ�������
// �汾��V2.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/01/07
//
// ��Ӧ���ţ�                SCL                 SDA
//            I2C2    PB6 / PB8(��ӳ��)    PB7 / PB9(��ӳ��)
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
  * @brief Ӳ��I2C2��ʼ�ź�
  * @return ��
  */
void I2C2_Hardware_StartSignal(void);

/**
  * @brief Ӳ��I2C2�����ź�
  * @return ��
  */
void I2C2_Hardware_StopSignal(void);

/**
  * @brief Ӳ��I2C2�����豸д��ַ
  * @param Address �ӻ���ַ
  * @return ��
  */
void I2C2_Hardware_SendWriteAddress(uint8_t Address);

/**
  * @brief Ӳ��I2C2�����豸����ַ
  * @param Address �ӻ���ַ
  * @return ��
  */
void I2C2_Hardware_SendReadAddress(uint8_t Address);

/**
  * @brief Ӳ��I2C2����һ�ֽ�����
  * @param I2CData ���͵�����
  * @return ��
  */
void I2C2_Hardware_SendData(uint8_t Data);

/**
  * @brief Ӳ��I2C2����һ�ֽ�����
  * @return ���յ�������
  */
uint8_t I2C2_Hardware_ReceiveData(void);

/**
  * @brief Ӳ��I2C2�ر�Ӧ���ź�
  * @return ��
  */
void I2C2_Hardware_CloseACKSignal(void);

/**
  * @brief Ӳ��I2C2��Ӧ���ź�
  * @return ��
  */
void I2C2_Hardware_OpenACKSignal(void);

#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/07/07
//				ʵ����Ӳ��IC�Ļ�������
// V2.0: 2024/01/07
//				��I2C�Ĺ���ԭ�ӻ���������븴���Լ����ݸ���ģ��
//
///////////////////////////////////////////////////////////
