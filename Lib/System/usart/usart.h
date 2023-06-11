#ifndef __SERIAL_H
#define __SERIAL_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����ڵ����������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/06/11
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

/* USART�˿����� */
#define USART_Number		USART1
#define USART_Port			GPIOA
#define USART_Pin_RX		GPIO_Pin_9
#define USART_Pin_TX		GPIO_Pin_10
#define USART_Periph				RCC_APB2Periph_USART1
#define USART_PortPeriph		RCC_APB2Periph_GPIOA
/* USART���� */
#define BaudRate		115200									// ������
#define Parity			USART_Parity_No					// У�鷽ʽ
#define StopBits		USART_StopBits_1				// ֹͣλ����
#define DataLength		USART_WordLength_8b		// ���ݳ���

/**
  * @brief ���ڳ�ʼ��
  * @return ��
  */
void Serial_Init(void);

/**
  * @brief ���ڷ���һ���ֽ�
  * @param Byte	Ҫ���͵�����
  * @return ��
  */
void Serial_SendByte(uint8_t Byte);

/**
  * @brief ���ڷ�������
  * @param Array	Ҫ���͵�����
  * @param Length	����ĳ��� / Ҫ���͵ĳ���
  * @return ��
  */
void Serial_SendArray(uint8_t* Array, uint16_t Length);

/**
  * @brief ���ڷ����ַ���
  * @param String	Ҫ���͵�����
  * @return ��
  */
void Serial_SendString(char* String);

/**
  * @brief ���ڷ�������
  * @param Number	Ҫ���͵�����
  * @param Length	���ֵĳ���
  * @return ��
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length);

/**
  * @brief ��ʽ���������׼C��printf��䣩
  * @return ��
  */
void Serial_printf(char *format, ...);

/**
  * @brief ��ý��ձ�־λ
  * @return �Ƿ��н��յ�����		0��û��
	* 													1����
  */
uint8_t Serial_GetRxFlag(void);

/**
  * @brief ��ý��յ�������
  * @return ���յ�������
  */
uint8_t Serial_GetRxData(void);

#endif
