#ifndef __MPU6050_H
#define __MPU6050_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�MPU6050�����ǵĻ�������
// �汾��V2.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/10/14
//
// ע����������16g�������
//     ���ٶ�ֵ / 32768 = x / 16 (����x��ʾ�����ϵ��������ٶ�)
//     ������ֵ / 32768 = x / 16 (����x��ʾ�����ϵĽ��ٶ�ֵ)     
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * �Ƿ�ʹ��SPI����
	*  0 ��ʾʹ�����I2C
	*  1 ��ʾʹ��I2C1
	*  2 ��ʾʹ��I2C2
	*/
#define whichI2C		0

/**
  * �Ƿ�ʹ�������˶�������DMP������̬����
	*  0 ��ʾ��ʹ��
	*  1 ��ʾʹ��
	*/
#define useDMP			1
// IMU�ɼ���Ƶ��
#define IMU_DEFAULT_HZ			100

/**
  * �Ƿ�ʹ���ж�
	*  0 ��ʾ��ʹ��
	*  1 ��ʾʹ��
	*/
#define MPU_Interrupt					1
#define MPU_INT_Periph				RCC_APB2Periph_GPIOB		// ����ʱ��
#define MPU_INT_Port					GPIOB										// IO�˿���
#define MPU_INT_Pin 					GPIO_Pin_5							// IO�˿�
#define MPU_INT_PortSource		GPIO_PortSourceGPIOB		// �ж�ԴIO�˿���
#define MPU_INT_PinSource 		GPIO_PinSource5 				// �ж�ԴIO�˿�
#define MPU_INT_EXTI_Line			EXTI_Line5							// �ж���
#define MPU_INT_EXTI_IRQn 		EXTI9_5_IRQn						// �ж�ͨ��

// X��Y��Z������ٶ�/������ԭʼ����
// ���±�0��5�ֱ��ǣ� AX�� AY�� AZ�� GX�� GY�� GZ
extern int16_t MPU6050_data[6];

/**
  * @brief MPU6050�����ǳ�ʼ��
  * @return ��
  */
void MPU6050_Init(void);

/**
  * @brief MPU6050��ȡ�ڼ�ID
  * @return ID��
  */
uint8_t MPU6050_GetID(void);

/**
  * @brief MPU6050��ȡ����
  * @return ��
  */
void MPU6050_READ(void);

#if useDMP == 1
/**
  * @brief DMP��ȡ�Ƕ�����
  * @param Pitch �����ǣ�����X����ת
  * @param Roll �����ǣ�����Y����ת
  * @param Yaw ƫ���ǣ�����Z����ת
  * @return ����0��ʾ��������
  */
uint8_t MPU_DMP_ReadAngle(float *Pitch, float *Roll, float *Yaw);

/**
  * @brief DMPд���ݣ�����DMP��ʹ�ã�
  * @param address �ӻ���ַ
  * @param command ָ��
  * @param array ��������
  * @param length ���ݳ��ȣ�����������
  * @return ��
  */
int DMP_Write(uint8_t SlaveAddr, uint8_t WriteAddr, u16 NumByteToWrite, uint8_t* pBuffer);

/**
  * @brief DMP�����ݣ�����DMP��ʹ�ã�
  * @param address �ӻ���ַ
  * @param reg ��ַ
  * @param array ��������
  * @param length ���ݳ��ȣ�����������
  * @return ��
  */
int DMP_Read(uint8_t SlaveAddr, uint8_t readAddr, u16 NumByteToRead, uint8_t* pBuffer);
#endif

#if MPU_Interrupt == 1
/**
  * @brief ����MPU6050���ж�����
  * @return ��
  */
void MPU6050_INT_Enable(void);

/**
  * @brief �ر�MPU6050���ж�����
  * @return ��
  */
void MPU6050_INT_Disable(void);
#endif

#endif


///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2024/07/17
//				ʵ���˶�ȡ������ٶȼƺͽ��ٶȼƵĹ���
// V2.0: 2024/10/14
//				��ֲ��eMPL��ʹ��DMP��ȡ����Ƕ�
//
///////////////////////////////////////////////////////////