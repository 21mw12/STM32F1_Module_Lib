#ifndef __MOTORENCODER_H
#define __MOTORENCODER_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����������ĵ������ʵ��
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/06/24
//
// ֱ�����:  ARR+1Ϊ1000   PSC+1Ϊ576
//           (�����PWMƵ��ѡ����һ����ά�ȵ����⣬�����趨��125Hz��
//           (������Դ��https://blog.csdn.net/u013273161/article/details/88316066)
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "TIM3Encoder.h"
#include "TIM2PWM.h"

/* �������IO������ */
#define Control_Periph		RCC_APB2Periph_GPIOA		// ����ʱ��
#define Control_PORT			GPIOA										// IO�˿���
#define Control_PIN_1 		GPIO_Pin_2							// IO�˿�
#define Control_PIN_2 		GPIO_Pin_3							// IO�˿�

/* ������ԣ���N20���Ϊ���� */
#define Gear_Ratio									51		// ���ֱȣ����ת��Ȧ����תһȦ��
#define HoareEncoder_Circle_Count		28		// ��������תһȦ�ļ���ֵ���ı�Ƶ��
#define Tyre_Perimeter							50		// ��̥�ܳ���cm��
#define Calculate_Time							1			// ������ʱ�䣨s��

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
void MotorEncoder_Init(void);

/**
  * @brief ���õ��״̬
  * @param state ״̬
  * @return ��
  */
void MotorEncoder_SetState(enum MotorState state);

/**
  * @brief ���õ����PWMռ�ձ�
  * @param Speed �ٶ�ֵ����Ҫ̫С�����Ҫֹͣ����ı���״̬��
  * @return ��
  */
void MotorEncoder_SetDutyCycle(int8_t DutyCycle);

/**
  * @brief ������̥ת���ٶ�
  * @return ��̥�ٶ�(��λcm/s)
	* ע����Ҫʹ�ö�ʱ��ÿ��һ��ʱ�����һ�Σ���ʱ����ʱ����Ҫ�޸��ڱ��ļ��ĵ�27��
  */
float MotorEncoder_CalculateSpeed(void);

#endif