#ifndef __MOTOR_H
#define __MOTOR_H

/////////////////////////////////////////////////////////////////////////////////////
//
// �ļ����ܣ��������ʵ��
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/12
//
// ֱ�����:  ARR+1Ϊ1000   PSC+1Ϊ576
//           (�����PWMƵ��ѡ����һ����ά�ȵ����⣬�����趨��125Hz��
//           (������Դ��https://blog.csdn.net/u013273161/article/details/88316066)
//
/////////////////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* �������IO������ */
#define Control_Periph		RCC_APB2Periph_GPIOA		// ����ʱ��
#define Control_Port			GPIOA										// IO�˿���
#define Control_Pin_1 		GPIO_Pin_2							// IO�˿�
#define Control_Pin_2 		GPIO_Pin_3							// IO�˿�

/* ���״̬�ṹ�� */
enum MotorState {
	ForwardTurn,	// ��ǰת
	ReverseTurn,	// ���ת
	Stop,					// ͣת
};

/**
  * @brief �����ʼ��
  * @return ��
  */
void Motor_Init(void);

/**
  * @brief ���õ��״̬
  * @param state ״̬
  * @return ��
  */
void Motor_SetState(enum MotorState state);

/**
  * @brief ���õ����PWMռ�ձ�
  * @param Speed �ٶ�ֵ����Ҫ̫С�����Ҫֹͣ����ı���״̬��
  * @return ��
  */
void Motor_SetDutyCycle(int8_t DutyCycle);

#endif
