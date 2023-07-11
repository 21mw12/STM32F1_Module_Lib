#ifndef __USART1_H
#define __USART1_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�����1�����������
// �汾��V1.2
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/11
//
// ��Ӧ���ţ�           	 TX        RX
//         		USART1		 P9			   PA10
//         		USART1     PA2       PA3
//         		USART3     PB10      PB11
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

/* USART���� */
#define USART1_BaudRate			115200									// ������
#define USART1_Parity				USART_Parity_No					// У�鷽ʽ
#define USART1_StopBits			USART_StopBits_1				// ֹͣλ����
#define USART1_DataLength		USART_WordLength_8b			// ���ݳ���

/* USART���ݰ�������� */
/* ע��!!!: Ҫ��USART1.c�ļ����������ͷź��������Ӧ�Ĵ����жϺ��� */
#define USART1_DataPackage_Length			10				// ���ݰ���󳤶�
#define USART1_DataPackageHead_HEX		0xFF			// ʮ���������ݰ��İ�ͷ
#define USART1_DataPackageTial_HEX		0x00			// ʮ���������ݰ��İ�β
#define USART1_DataPackageHead_TEXT		'@'				// �ı����ݰ��İ�ͷ  ����βĬ��ΪWindowsƽ̨�Ļ��з���\r\n����

/* ���ڽ������� */
extern uint8_t USART1_RxData;
/**
	*  Serial_RxPacket���飨ʮ���������ݰ����飩���ͣ�
	*  ����ĵ�һλ(�±�0)��ʾ��Ч�������� �ڶ�λ(�±�1)��ʼ��������������
	*/
extern uint8_t USART1_RxPacket[USART1_DataPackage_Length];
/* Serial_DataString���飨�ı����ݰ����飩 */
extern char USART1_DataString[USART1_DataPackage_Length];


/**
  * @brief ���ڳ�ʼ��
  * @return ��
  */
void USART1_Init(void);

/**
  * @brief ���ڷ���һ���ֽ�
  * @param Byte	Ҫ���͵�����
  * @return ��
  */
void USART1_SendByte(uint8_t Byte);

/**
  * @brief ���ڷ�������
  * @param Array	Ҫ���͵�����
  * @param Length	����ĳ��� / Ҫ���͵ĳ���
  * @return ��
  */
void USART1_SendArray(uint8_t* Array, uint16_t Length);

/**
  * @brief ���ڷ����ַ���
  * @param String	Ҫ���͵�����
  * @return ��
  */
void USART1_SendString(char* String);

/**
  * @brief ���ڷ�������
  * @param Number	Ҫ���͵�����
  * @param Length	���ֵĳ���
  * @return ��
  */
void USART1_SendNumber(uint32_t Number, uint8_t Length);

/**
  * @brief ��ʽ���������׼C��printf��䣩
  * @return ��
  */
void USART1_printf(char *format, ...);

/**
  * @brief ��ý��ձ�־λ
  * @return �Ƿ��н��յ�����		0��û��
	* 													1����
  */
uint8_t USART1_GetRxFlag(void);

/**
  * @brief ��ý��յ�������
  * @return ���յ�������
  */
uint8_t USART1_GetRxData(void);

/**
  * @brief ����ʮ���������ݰ�
  * @param dataArray ��������
  * @param dataLength ���ݳ���
  * @return ��
  */
void USART1_SendDatePackage_HEX(uint8_t* dataArray, uint16_t dataLength);

/**
  * @brief �����ı����ݰ�
  * @param String	�ı�����
  * @return ��
  */
void USART1_SendDatePackage_TEXT(char* String);

#endif


///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/06/11
//				ʵ���˻����Ĵ��ڽ��շ��͹���
// V1.1: 2023/06/13
//				ʵ���˴��ڷ��ͽ��ղ��������ݰ���
// 				����ʮ���������ݰ����ı����ݰ�
// V1.2: 2023/07/11
//				ʵ�����������ڵĹ���
//
///////////////////////////////////////////////////////////
