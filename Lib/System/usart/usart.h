#ifndef __SERIAL_H
#define __SERIAL_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����ڵ����������
// �汾��V1.1
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/06/13
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

/* USART���ݰ�������ã�ע���ͷź��������Ӧ�Ĵ����жϺ����� */
#define DataPackage_Length		10				// ���ݰ���󳤶�
#define DataPackageHead_HEX		0xFF		// ʮ���������ݰ��İ�ͷ
#define DataPackageTial_HEX		0x00		// ʮ���������ݰ��İ�β
#define DataPackageHead_TEXT	'@'			// �ı����ݰ��İ�ͷ  ����βĬ��ΪWindowsƽ̨�Ļ��з���\r\n����

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

/**
  * @brief ����ʮ���������ݰ�
  * @param dataArray ��������
  * @param dataLength ���ݳ���
  * @return ��
  */
void Serial_SendDatePackage_HEX(uint8_t* dataArray, uint16_t dataLength);

/**
  * @brief �����ı����ݰ�
  * @param String	�ı�����
  * @return ��
  */
void Serial_SendDatePackage_TEXT(char* String);

#endif


///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/06/11
//				ʵ���˻����Ĵ��ڽ��շ��͹���
// V1.1: 2023/06/13
//				ʵ���˴��ڷ��ͽ��ղ��������ݰ���
// 				����ʮ���������ݰ����ı����ݰ�
//
///////////////////////////////////////////////////////////
