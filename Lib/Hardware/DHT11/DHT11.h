#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�DHT11��ʪ�ȴ�����ģ��Ĺ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/4/26
//
///////////////////////////////////////////////////////////

/* DHT11���ݾ��� */
#define DHT11_Data_Accurate		1

/* DHT11����������Ϣ */
#define DHT11_Periph		RCC_APB2Periph_GPIOA		// ����ʱ��
#define DHT11_PORT			GPIOA										// IO�˿���
#define DHT11_PIN 			GPIO_Pin_11							// IO�˿�

/**
  * @brief ��ʪ��������ʼ��
  * @return ��ʼ��״̬		0��ʧ�� 
	* 										1���ɹ�
  */
uint8_t DHT11_Init(void);

/**
  * @brief ��ȡһ������
  * @param temp �¶�ֵ ��Χ:0��~50��
  * @param humi ʪ��ֵ ��Χ:20%~90%
  * @return ���ݽ���״̬		0��ʧ�� 
	* 											1������
  */
uint8_t DHT11_ReadData(uint8_t *temp, uint8_t *humi);

#endif















