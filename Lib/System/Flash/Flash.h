#ifndef __FLASH_H
#define __FLASH_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�Ƭ��Flash����ع��ܺ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/01/02
//
// ע��ʹ��Flash�洢����ʱҪ����ʹ�����һҳ����ֹ���ǳ�������
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * @brief ��Flash��д��һ���֣�32λ��
  * @param Address Flash�ĵ�ַ
  * @param Data д�������
  * @return ��
  */
void FLASH_WriteWord(uint32_t Address, uint32_t Data);

/**
  * @brief ��Flash��д��һ�����֣�16λ��
  * @param Address Flash�ĵ�ַ
  * @param Data д�������
  * @return ��
  */
void FLASH_WriteHalfWord(uint32_t Address, uint16_t Data);

/**
  * @brief ��Flash�ж���һ���֣�32λ��
  * @param Address Flash�ĵ�ַ
  * @return ����������
  */
uint32_t FLASH_ReadWord(uint32_t Address);

/**
  * @brief ��Flash�ж���һ�����֣�16λ��
  * @param Address Flash�ĵ�ַ
  * @return ����������
  */
uint16_t FLASH_ReadHalfWord(uint32_t Address);

/**
  * @brief ��Flash�ж���һ���ֽڣ�8λ��
  * @param Address Flash�ĵ�ַ
  * @return ����������
  */
uint8_t FLASH_ReadByte(uint32_t Address);

/**
  * @brief ��������Flash����
  * @return ��
  */
void FLASH_ClearAllPages(void);

/**
  * @brief ��������Flash��һҳ
  * @param PageAddress Flashҳ���׵�ַ
  * @return ��
  */
void FLASH_ClearPage(uint32_t PageAddress);

/**
  * @brief ��ȡFlash��С
  * @return Flash��С
  */
uint16_t FLASH_GetSTM32_FLASHSIZE(void);

/**
  * @brief ��ȡSTM32оƬ��ID��
  * @param ChipID0 ID�����λ
  * @param ChipID1 ID���м�λ
  * @param ChipID2 ID����߸�
  * @return ��
  */
void FLASH_GetSTM32_ChipID(uint32_t* ChipID0, uint32_t* ChipID1, uint32_t* ChipID2);

#endif
