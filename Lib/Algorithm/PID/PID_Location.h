#ifndef __PID_LOCATION_H
#define __PID_LOCATION_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�λ��ʽPID
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
	float err_sum;		// ����
	
	float target;			// Ŀ��ֵ
} PID_Location_Struct;

/**
  * @brief ����ʽPID��ʼ��
  * @param pid PID�ṹ��
  * @param Kp pֵ
  * @param Ki iֵ
  * @param Kd dֵ
  * @return ��
  */
void PID_Location_Init(PID_Location_Struct* pid, float Kp, float Ki, float Kd);

/**
  * @brief ����ʽPID����Ŀ��ֵ
  * @param pid PID�ṹ��
  * @param NewTarget ��ǰĿ��
  * @return ��
  */
void PID_Location_SetTarget(PID_Location_Struct* pid, float NewTarget);

/**
  * @brief ����ʽPID����
  * @param pid PID�ṹ��
  * @param NowValue ��ǰֵ
  * @return �������
  */
float PID_Location_Calculate(PID_Location_Struct* pid, float NowValue);

#endif
