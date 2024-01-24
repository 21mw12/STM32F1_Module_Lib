#ifndef __W25QXX_H
#define __W25QXX_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�W25QXXϵ��оƬ
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/12/27
//
// ע���ڽ�Э�Ƽ��Ĵ����������ͨ���Ե��޸�
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* W25QXXоƬ�˿���Ϣ */
#define W25QXX_GPIOPeriph		RCC_APB2Periph_GPIOA
#define W25QXX_Port					GPIOA
#define W25QXX_Pin_CS				GPIO_Pin_4

/**
  * @brief W25QXXϵ��оƬ��ʼ��
  * @return ��
  */
void W25QXX_Init(void);

/**
  * @brief W25QXXоƬ��ID
  * @param MID ����ID
  * @param DID �豸ID
  * @return ��
  */
void W25QXX_ReadID(uint8_t* MID, uint16_t* DID);

/**
  * @brief W25QXXоƬ���д����
  * @return ��
  */
void W25QXX_RelieveWriteProtect(void);

/**
  * @brief W25QXXоƬд����
  * @param address д��ҳ��ַ��xxxx00~xxxxFF��
  * @param dataArray д����������
  * @param count д���������������д256���������Ḳ�ǵ�һ����
  * @return ��
	* ע�����д����ǰ��������ʹ�� �������� = ԭʼ���� & ��д�������
  */
void W25QXX_WritePage(uint32_t address, uint8_t* dataArray, uint16_t count);

/**
  * @brief W25QXXоƬ������
  * @param address ����ҳ��ַ��xxxx00~xxxxFF��
  * @param dataArray ������������
  * @param count �����������������������ƣ�
  * @return ��
  */
void W25QXX_ReadPage(uint32_t address, uint8_t* dataArray, uint32_t count);

/**
  * @brief W25QXXоƬ��������(4KB)
  * @param address ������ַ��xxx000~xxxFFF��
  * @return ��
	* ע���������ݺ���������Ϊ0xFF
  */
void W25QXX_SectorErase(uint32_t address);

/**
  * @brief W25QXXоƬ������(64KB)
  * @param address ���ַ��xx0000~xxFFFF��
  * @return ��
  */
void W25QXX_BlockErase(uint32_t address);

#endif
