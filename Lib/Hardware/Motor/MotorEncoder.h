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

/* �������IO������ */
#define Control_Periph		RCC_APB2Periph_GPIOA		// ����ʱ��
#define Control_Port			GPIOA										// IO�˿���
#define Control_Pin_1 		GPIO_Pin_2							// IO�˿�
#define Control_Pin_2 		GPIO_Pin_3							// IO�˿�

/* ������ԣ���N20���Ϊ���� */
#define Gear_Ratio									51		// ���ֱȣ����ת��Ȧ����תһȦ��
#define HoareEncoder_Circle_Count		28		// ��������תһȦ�ļ���ֵ���ı�Ƶ��
#define Tyre_Perimeter							13.5	// ��̥�ܳ���cm��
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
void MotorEncoder_SetDutyCycle(uint16_t DutyCycle);

/**
  * @brief ������̥ת����RPM
  * @return ���ӵ�RPS(��λ��ת/��)
	* ע����Ҫʹ�ö�ʱ��ÿ��һ��ʱ�����һ�Σ���ʱ����ʱ����Ҫ�޸��ڱ��ļ��ĵ�27��
  */
float MotorEncoder_CalculateRPS(enum MotorState state);

/**
  * @brief ������̥ת�����ٶ�
  * @return ���ӵ����ٶ�(��λ������/��)
	* ע����Ҫʹ�ö�ʱ��ÿ��һ��ʱ�����һ�Σ���ʱ����ʱ����Ҫ�޸��ڱ��ļ��ĵ�27��
  */
float MotorEncoder_CalculateSpeed(enum MotorState state);

/**
  * @brief ������̥ת���ľ���
  * @return ���еľ���(��λ������)
	* ע����Ҫʹ�ö�ʱ��ÿ��һ��ʱ�����һ�Σ���ʱ����ʱ����Ҫ�޸��ڱ��ļ��ĵ�27��
  */
float MotorEncoder_CalculateDistance(enum MotorState state);


#endif
