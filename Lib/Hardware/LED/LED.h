#ifndef __LED_H
#define __LED_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�ʹ��STM32ϵ�е�Ƭ��ʱLED����ع��ܺ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/04/21
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* LED����״̬��0��ʾ�ߵ�ƽ������1��ʾ�͵�ƽ���� */
#define LED_PIN_STATE		0

/* LED����������Ϣ */
#define LED_Periph		RCC_APB2Periph_GPIOC		// ����ʱ��
#define LED_PORT			GPIOC										// IO�˿���
#define LED_PIN 			GPIO_Pin_13							// IO�˿�

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
  * @brief LED��˸
  * @return ��
  */
void LED_Flash(int ms);

#endif
