#ifndef __USART3_H
#define __USART3_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�����2�����������
// �汾��V1.2
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/11
//
// ��Ӧ���ţ�           	 TX        RX
//         		USART3		 P9			   PA10
//         		USART3     PA2       PA3
//         		USART3     PB10      PB11
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

/* USART���� */
#define USART3_BaudRate			115200									// ������
#define USART3_Parity				USART_Parity_No					// У�鷽ʽ
#define USART3_StopBits			USART_StopBits_1				// ֹͣλ����
#define USART3_DataLength		USART_WordLength_8b			// ���ݳ���

/* USART���ݰ�������� */
/* ע��!!!: Ҫ��USART3.c�ļ����������ͷź��������Ӧ�Ĵ����жϺ��� */
#define USART3_DataPackage_Length			10				// ���ݰ���󳤶�
#define USART3_DataPackageHead_HEX		0xFF			// ʮ���������ݰ��İ�ͷ
#define USART3_DataPackageTial_HEX		0x00			// ʮ���������ݰ��İ�β
#define USART3_DataPackageHead_TEXT		'@'				// �ı����ݰ��İ�ͷ  ����βĬ��ΪWindowsƽ̨�Ļ��з���\r\n����

/* ���ڽ������� */
extern uint8_t USART3_RxData;
/**
	*  Serial_RxPacket���飨ʮ���������ݰ����飩���ͣ�
	*  ����ĵ�һλ(�±�0)��ʾ��Ч�������� �ڶ�λ(�±�1)��ʼ��������������
	*/
extern uint8_t USART3_RxPacket[USART3_DataPackage_Length];
/* Serial_DataString���飨�ı����ݰ����飩 */
extern char USART3_DataString[USART3_DataPackage_Length];


/**
  * @brief ���ڳ�ʼ��
  * @return ��
  */
void USART3_Init(void);

/**
  * @brief ���ڷ���һ���ֽ�
  * @param Byte	Ҫ���͵�����
  * @return ��
  */
void USART3_SendByte(uint8_t Byte);

/**
  * @brief ���ڷ�������
  * @param Array	Ҫ���͵�����
  * @param Length	����ĳ��� / Ҫ���͵ĳ���
  * @return ��
  */
void USART3_SendArray(uint8_t* Array, uint16_t Length);

/**
  * @brief ���ڷ����ַ���
  * @param String	Ҫ���͵�����
  * @return ��
  */
void USART3_SendString(char* String);

/**
  * @brief ���ڷ�������
  * @param Number	Ҫ���͵�����
  * @param Length	���ֵĳ���
  * @return ��
  */
void USART3_SendNumber(uint32_t Number, uint8_t Length);

/**
  * @brief ��ý��ձ�־λ
  * @return �Ƿ��н��յ�����		0��û��
	* 													1����
  */
uint8_t USART3_GetRxFlag(void);

/**
  * @brief ��ý��յ�������
  * @return ���յ�������
  */
uint8_t USART3_GetRxData(void);

/**
  * @brief ����ʮ���������ݰ�
  * @param dataArray ��������
  * @param dataLength ���ݳ���
  * @return ��
  */
void USART3_SendDatePackage_HEX(uint8_t* dataArray, uint16_t dataLength);

/**
  * @brief �����ı����ݰ�
  * @param String	�ı�����
  * @return ��
  */
void USART3_SendDatePackage_TEXT(char* String);

#endif
