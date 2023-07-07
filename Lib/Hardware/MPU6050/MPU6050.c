#include "MPU6050.h"

// X��Y��Z������ٶ�/������ԭʼ����
// ���±�0��5�ֱ��ǣ� AX�� AY�� AZ�� GX�� GY�� GZ
uint16_t MPU6050_data[5];

/**
  * @brief  MPU6050д����
  * @param  writeAddr �Ĵ�����ַ
  * @param  data Ҫд�������
  * @retval ��
  */
void MPU6050_WriteData(uint8_t writeAddr, uint8_t data) {
	I2C_Bus_SendByte(MPU6050_ADDRESS, writeAddr, data);
}

/**
  * @brief  MPU6050������
  * @param  writeAddr �Ĵ�����ַ
  * @param  dataArray Ҫ����������
  * @param  length Ҫ����������
  * @retval ��
  */
void MPU6050_ReaData(uint8_t writeAddr, uint8_t* dataArray, uint16_t length) {
	I2C_Bus_ReadArray(MPU6050_ADDRESS, writeAddr, dataArray, length);
}

/**
  * @brief 	����MPU6050�����Ǵ����������̷�Χ
  * @param 	fsr �����Ǵ����������̷�Χ
	* 						0 �� ��250dps
	* 						1 �� ��500dps
	* 						2 �� ��1000dps
	* 						3 �� ��2000dps
  * @return ��
  */
void MPU6050_Set_Gyro_Fsr(uint8_t fsr) {
	MPU6050_WriteData(MPU6050_GYRO_CFG, fsr<<3);
}

/**
  * @brief 	����MPU6050�����Ǵ����������̷�Χ
  * @param 	fsr ���ٶȴ����������̷�Χ
	* 						0 �� ��2g
	* 						1 �� ��4g
	* 						2 �� ��8g
	* 						3 �� ��16g
  * @return ��
  */
void MPU6050_Set_Accel_Fsr(uint8_t fsr) {
	MPU6050_WriteData(MPU6050_ACCEL_CFG, fsr<<3);
}

/**
  * @brief 	����MPU6050���ֵ�ͨ�˲���
  * @param 	lpf ���ֵ�ͨ�˲�Ƶ��(Hz)
  * @return ��
  */
void MPU6050_Set_LPF(uint16_t lpf) {
	uint8_t data = 0;
	if (lpf >= 188) data = 1;
	else if (lpf >= 98) data=  2;
	else if (lpf >= 42) data = 3;
	else if (lpf >= 20) data = 4;
	else if (lpf >= 10) data = 5;
	else data = 6;
	
	MPU6050_WriteData(MPU6050_CFG, data);
}

/**
  * @brief 	����MPU6050���ֵ�ͨ�˲���(�ٶ�Fs=1KHz)
  * @param 	rate �����ʣ�4~1000Hz��
  * @return ��
  */
void MPU6050_Set_Rate(uint16_t rate) {
	uint8_t data;
	if (rate > 1000) rate = 1000;
	if (rate < 4) rate = 4;
	data = 1000 / rate - 1;
	
	MPU6050_WriteData(MPU6050_SAMPLE_RATE, data);
 	MPU6050_Set_LPF(rate / 2);	// �Զ�����LPFΪ�����ʵ�һ��
}


void MPU6050_Init(void) {	
	uint8_t res;
	
	MPU6050_WriteData(MPU6050_PWR_MGMT1, 0X80);		// ��λMPU6050
  Delay_ms(100);
	MPU6050_WriteData(MPU6050_PWR_MGMT1, 0X00);		// ����MPU6050
	MPU6050_Set_Gyro_Fsr(3);											// �����Ǵ�����,��2000dps
	MPU6050_Set_Accel_Fsr(0);											// ���ٶȴ�����,��2g
	MPU6050_Set_Rate(50);													// ���ò�����50Hz
	MPU6050_WriteData(MPU6050_INT_EN, 0X00);			// �ر������ж�
	MPU6050_WriteData(MPU6050_USER_CTRL, 0X00);		// I2C��ģʽ�ر�
	MPU6050_WriteData(MPU6050_FIFO_EN, 0X00);			// �ر�FIFO
	MPU6050_WriteData(MPU6050_INTBP_CFG, 0X80);		// INT���ŵ͵�ƽ��Ч

	MPU6050_ReaData(MPU6050_DEVICE_ID, &res, 1);

	if(res == MPU6050_ADDRESS) {
		MPU6050_WriteData(MPU6050_PWR_MGMT1, 0X01);	// ����CLKSEL,PLL X��Ϊ�ο�
		MPU6050_WriteData(MPU6050_PWR_MGMT2, 0X00);	// ���ٶ��������Ƕ�����
		MPU6050_Set_Rate(50);												// ���ò�����Ϊ50Hz
 	}
}

uint8_t MPU6050_GetID(void) {
	uint8_t ID;
	MPU6050_ReaData(MPU6050_WHO_AM_I, &ID, 1);
	return ID;
}

void MPU6050_READ(void) {
	uint8_t original_data[14];
	
	// �������������ݵ�ַ�������˼��ٶȺ������ǹ�12�ֽ�
	MPU6050_ReaData(MPU6050_ACCEL_XOUTH, original_data, 14);
	
	// ��������������
	for(uint8_t i = 0; i < 3; i++)
		MPU6050_data[i] = ((original_data[2 * i] << 8) + original_data[2 * i + 1]);
	for(uint8_t i = 4; i < 7; i++)
		MPU6050_data[i - 1] = ((original_data[2 * i] << 8) + original_data[2 * i +1 ]);        
}

