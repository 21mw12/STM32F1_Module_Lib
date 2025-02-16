#ifndef __LED_H
#define __LED_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�LED����ع��ܺ���
// �汾��V1.1
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/04/27
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* LED����״̬��0��ʾ�ߵ�ƽ������1��ʾ�͵�ƽ���� */
#define LED_Pin_State		0

/* LED����������Ϣ */
#define LED_Periph		RCC_APB2Periph_GPIOC		// ����ʱ��
#define LED_Port			GPIOC										// IO�˿���
#define LED_Pin 			GPIO_Pin_13							// IO�˿�

/**
  * @brief LED��ʼ��
  * @return ��
  */
void LED_Init(void);

/**
  * @brief LED����
  * @return ��
  */
void LED_ON(void);

/**
  * @brief LEDϨ��
  * @return ��
  */
void LED_OFF(void);

/**
  * @brief LED״̬��ת
  * @return ��
  */
void LED_Turn(void);

/**
  * @brief LED��˸
	* @param ms ��˸����ĺ�����
  * @return ��
  */
void LED_Flash(int ms);

#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/04/21
//				ʵ����LED�������Լ�LED����˸����
// V1.1: 2023/04/27
//				ʵ����LED��״̬��ת����
//
///////////////////////////////////////////////////////////
