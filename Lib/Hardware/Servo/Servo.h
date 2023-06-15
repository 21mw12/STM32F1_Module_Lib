#ifndef __SERVO_H
#define __SERVO_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�����Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/06/15
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "pwm.h"

/**
  * @brief �����ʼ��
  * @return ��
  */
void Servo_Init(void);

/**
  * @brief ���ö���Ƕ�
  * @param Angle �Ƕ�ֵ
  * @return ��
  */
void Servo_SetAngle(float Angle);

#endif
