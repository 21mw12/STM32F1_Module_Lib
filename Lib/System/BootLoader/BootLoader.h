#ifndef __BOOTLOADER_H
#define __BOOTLOADER_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�ʵ��BootLoader���ܣ���ͨ����U-boot����APP����
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2025/02/16
// ע����Ҫ����ʹ�ã���ʹ��ģ��
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * @brief ����APP����
  * @param App_Vector APP����¼��ʼ��ַ
  */
void BootLoader_LoadAPP(uint32_t App_Vector);

#endif
