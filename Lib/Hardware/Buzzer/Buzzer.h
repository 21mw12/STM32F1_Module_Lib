#ifndef __BUZZER_H
#define __BUZZER_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ���Դ�������Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/02
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ����������������Ϣ */
#define BUZZER_Periph		RCC_APB2Periph_GPIOC		// ����ʱ��
#define BUZZER_PORT			GPIOC										// IO�˿���
#define BUZZER_PIN 			GPIO_Pin_14							// IO�˿�

/**
  * @brief ��������ʼ��
  * @return ��
  */
void Buzzer_Init(void);

/**
  * @brief ��������
  * @return ��
  */
void BUZZER_ON(void);

/**
  * @brief �������ر�
  * @return ��
  */
void BUZZER_OFF(void);

#endif
