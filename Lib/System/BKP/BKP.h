#ifndef __BKP_H
#define __BKP_H

///////////////////////////////////////////////////////////

// �ļ����ܣ�BPK����ع��ܺ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/12/30
//
// ע����Ҫ��VBAT����һ��1.8~3.6V�ĵ�Դ
//		 С����������20�ֽ� / �������ͻ�������84�ֽ�
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * @brief BKP��ʼ��
  * @return ��
  */
void BKP_Init(void);

/**
  * @brief д��BKP
  * @param BKP_Add BKP�ĵ�ַ
  * @param Data Ҫд�������
  * @return ��
  */
#define BKP_Write(BKP_Add, Data)		BKP_WriteBackupRegister(BKP_Add, Data)

/**
  * @brief ����BKP
  * @param BKP_Add BKP�ĵ�ַ
  * @return ��Ӧ��ַ�е�����
  */
#define BKP_Read(BKP_Add)						BKP_ReadBackupRegister(BKP_Add)

#endif
