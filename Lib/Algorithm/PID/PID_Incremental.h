#ifndef __PID_INCREMENTAL_H
#define __PID_INCREMENTAL_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�����ʽPID
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/08/24
//
///////////////////////////////////////////////////////////

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	
	float err;				// ��ǰ���
	float err_last;		// ��һ�����
	float err_pass;		// ���ϴ����
	
	float target;			// Ŀ��ֵ
} PID_Incremental_Struct;

/**
  * @brief ����ʽPID��ʼ��
  * @param pid PID�ṹ��
  * @param Kp pֵ
  * @param Ki iֵ
  * @param Kd dֵ
  * @return ��
  */
void PID_Incremental_Init(PID_Incremental_Struct* pid, float Kp, float Ki, float Kd);

/**
  * @brief ����ʽPID����Ŀ��ֵ
  * @param pid PID�ṹ��
  * @param NewTarget ��ǰĿ��
  * @return ��
  */
void PID_Incremental_SetTarget(PID_Incremental_Struct* pid, float NewTarget);

/**
  * @brief ����ʽPID����
  * @param pid PID�ṹ��
  * @param NowValue ��ǰֵ
  * @return �������
  */
float PID_Incremental_Calculate(PID_Incremental_Struct* pid, float NowValue);

#endif
