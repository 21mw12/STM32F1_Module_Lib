#ifndef __MPU6050_H
#define __MPU6050_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�MPU6050�����ǵĻ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/07
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"
#include "MPU6050_Register.h"
#include "I2C1Hardware.h"

extern uint16_t MPU6050_data[5];

/**
  * @brief MPU6050�����ǳ�ʼ��
  * @return ��
  */
void MPU6050_Init(void);

uint8_t MPU6050_GetID(void);

void MPU6050_READ(void);

#endif
