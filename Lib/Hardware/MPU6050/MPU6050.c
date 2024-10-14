#include "MPU6050.h"
#include "delay.h"
#include "MPU6050_Register.h"
#if whichI2C == 0
#include "I2CSoftware.h"
//#elif whichI2C == 1
//#include "I2C1Hardware.h"
//#else
//#include "I2C2Hardware.h"
#endif
#if useDMP == 1
#include <math.h>
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#endif

int16_t MPU6050_data[6];

#if MPU_Interrupt == 1
/**
  * @brief  MPU6050�ж����ų�ʼ��
  * @retval ��
  */
void MPU6050_INT_Init(void) {
	RCC_APB2PeriphClockCmd(MPU_INT_Periph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = MPU_INT_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MPU_INT_Port, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(MPU_INT_PortSource, MPU_INT_PinSource); 
	
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = MPU_INT_EXTI_Line ;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = MPU_INT_EXTI_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 6;
	NVIC_Init(&NVIC_InitStruct);
}

void MPU6050_INT_Enable(void) {
	EXTI->IMR &= ~(MPU_INT_EXTI_Line);
}

void MPU6050_INT_Disable(void) {
	EXTI->IMR |= MPU_INT_EXTI_Line;
}
#endif

#if whichI2C == 0
/**
  * @brief  MPU6050д����
  * @param  writeAddr �Ĵ�����ַ
  * @param  data Ҫд�������
  * @retval ��
  */
void MPU6050_WriteData(uint8_t writeAddr, uint8_t data) {
	I2C_Software_StartSignal();
	I2C_Software_SendData(MPU6050_ADDRESS << 1);
	I2C_Software_SendData(writeAddr);
	I2C_Software_SendData(data); 
	I2C_Software_StopSignal();
}

/**
  * @brief  MPU6050������
  * @param  writeAddr �Ĵ�����ַ
  * @param  dataArray Ҫ����������
  * @param  length Ҫ����������
  * @retval ��
  */
void MPU6050_ReaData(uint8_t readAddr, uint8_t* dataArray, uint16_t length) {
	I2C_Software_StartSignal();
	I2C_Software_SendData(MPU6050_ADDRESS << 1);
	I2C_Software_SendData(readAddr);
	
	I2C_Software_StartSignal();
	I2C_Software_SendData(MPU6050_ADDRESS << 1 | 0x01);
	
	for (uint16_t i = 0; i < length; i++) {
		*(dataArray + i) = I2C_Software_ReceiveByte();
		I2C_Software_SendAck((i + 1 == length) ? 1 : 0);
	}
	I2C_Software_StopSignal();
}

#else

#if whichI2C == 1
#define I2CX	I2C1
#elif whichI2C == 2
#define I2CX	I2C2
#endif

#define Timeout	10000

/**
  * @brief Ӳ��I2C�ȴ��¼�
  * @param I2C_EVENT I2C�¼� 
  * @return ��
  */
void MPU6050_WaitEvent(uint32_t I2C_EVENT) {
	uint32_t To = Timeout;
	while (I2C_CheckEvent(I2CX, I2C_EVENT) != SUCCESS){
		To--;
		if (To == 0) {
			/* ��ʱ�Ĵ�������룬������ӵ��˴� */
			break;
		}
	}
}

void MPU6050_WriteData(uint8_t writeAddr, uint8_t data) {
	I2C_GenerateSTART(I2CX, ENABLE);										//Ӳ��I2C������ʼ����
	MPU6050_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);					//�ȴ�EV5
	
	I2C_Send7bitAddress(I2CX, MPU6050_ADDRESS, I2C_Direction_Transmitter);	//Ӳ��I2C���ʹӻ���ַ������Ϊ����
	MPU6050_WaitEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//�ȴ�EV6
	
	I2C_SendData(I2CX, writeAddr);											//Ӳ��I2C���ͼĴ�����ַ
	MPU6050_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING);			//�ȴ�EV8
	
	I2C_SendData(I2CX, data);												//Ӳ��I2C��������
	MPU6050_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//�ȴ�EV8_2
	
	I2C_GenerateSTOP(I2CX, ENABLE);											//Ӳ��I2C������ֹ����
}

/* ������ֽ���BUG */
void MPU6050_ReaData(uint8_t readAddr, uint8_t* dataArray, uint16_t length) {	
	I2C_GenerateSTART(I2CX, ENABLE);										//Ӳ��I2C������ʼ����
	MPU6050_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);					//�ȴ�EV5
	
	I2C_Send7bitAddress(I2CX, MPU6050_ADDRESS, I2C_Direction_Transmitter);	//Ӳ��I2C���ʹӻ���ַ������Ϊ����
	MPU6050_WaitEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//�ȴ�EV6
	
	I2C_SendData(I2CX, readAddr);											//Ӳ��I2C���ͼĴ�����ַ
	MPU6050_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//�ȴ�EV8_2
	
	I2C_GenerateSTART(I2CX, ENABLE);										//Ӳ��I2C�����ظ���ʼ����
	MPU6050_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);					//�ȴ�EV5
	
	I2C_Send7bitAddress(I2CX, MPU6050_ADDRESS, I2C_Direction_Receiver);		//Ӳ��I2C���ʹӻ���ַ������Ϊ����
	MPU6050_WaitEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);		//�ȴ�EV6
	
	for (uint16_t i = 0; i < length; i++) {
		if (i + 1 == length) {
			I2C_AcknowledgeConfig(I2CX, DISABLE);									//�ڽ������һ���ֽ�֮ǰ��ǰ��Ӧ��ʧ��
			I2C_GenerateSTOP(I2CX, ENABLE);											//�ڽ������һ���ֽ�֮ǰ��ǰ����ֹͣ����
		}
		
		MPU6050_WaitEvent(I2C_EVENT_MASTER_BYTE_RECEIVED);				//�ȴ�EV7
		*(dataArray + i) = I2C_ReceiveData(I2CX);											//�������ݼĴ���
	}
	
	I2C_AcknowledgeConfig(I2CX, ENABLE);									//��Ӧ��ָ�Ϊʹ�ܣ�Ϊ�˲�Ӱ��������ܲ����Ķ�ȡ���ֽڲ���
}
#endif

#if useDMP == 0

void MPU6050_Init(void) {
	MPU6050_WriteData(MPU6050_PWR_MGMT1, 0X01);  	// ȡ��˯��ģʽ��ѡ��ʱ��ԴΪX��������
	MPU6050_WriteData(MPU6050_PWR_MGMT2, 0X00); 	// �������������
	MPU6050_WriteData(MPU6050_SAMPLE_RATE, 0x09);	// �����ʷ�Ƶ�Ĵ��������ò�����
	MPU6050_WriteData(MPU6050_CFG, 0x06);					// ���üĴ���������DLPF
	MPU6050_WriteData(MPU6050_GYRO_CFG, 0x18);    // ���������üĴ�����ѡ��������Ϊ��2000��/s
	MPU6050_WriteData(MPU6050_ACCEL_CFG, 0x18);   // ���ٶȼ����üĴ�����ѡ��������Ϊ��16g
	
#if MPU_Interrupt == 1
	MPU6050_INT_Init();
#endif
}

#else
// ������Ԫ������
#define q30  1073741824.0f
// ���������ǵĳ�ʼ����
static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};

/**
  * @brief  �������Լ죬����DMP��ƫ��
  * @retval ��
  */
static void DMP_SelfTest(void) {
	int result;
	long gyro[3], accel[3];

	result = mpu_run_self_test(gyro, accel);
	if (result == 0x7) {
		/* Test passed. We can trust the gyro data here, so let's push it down
		 * to the DMP.
		 */
		float sens;
		unsigned short accel_sens;
		mpu_get_gyro_sens(&sens);
		gyro[0] = (long)(gyro[0] * sens);
		gyro[1] = (long)(gyro[1] * sens);
		gyro[2] = (long)(gyro[2] * sens);
		dmp_set_gyro_bias(gyro);
		mpu_get_accel_sens(&accel_sens);
		accel[0] *= accel_sens;
		accel[1] *= accel_sens;
		accel[2] *= accel_sens;
		dmp_set_accel_bias(accel);
		// printf("setting bias succesfully ......\r\n");
	}
}

/**
  * @brief  ��������ת��Ϊ����ģʽ
  * @retval ����ģʽ
  */
static unsigned short DMP_Row2Scale(const signed char *row) {
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

/**
  * @brief  ����λ����ת��Ϊ����ģʽ
  * @retval ����ģʽ
  */
static unsigned short DMP_OrientationMatrix_2Scalar(const signed char *mtx) {
	unsigned short scalar;
	scalar = DMP_Row2Scale(mtx);
	scalar |= DMP_Row2Scale(mtx + 3) << 3;
	scalar |= DMP_Row2Scale(mtx + 6) << 6;
	return scalar;
}

int DMP_Write(uint8_t SlaveAddr, uint8_t WriteAddr, u16 NumByteToWrite, uint8_t* pBuffer) {
	I2C_Software_StartSignal();
	
	I2C_Software_SendData(SlaveAddr<<1);
	I2C_Software_SendData(WriteAddr);
	
	for (uint16_t i = 0; i < NumByteToWrite; i++) {
		I2C_Software_SendData(*(pBuffer + i)); 
	}
	
	I2C_Software_StopSignal();
  return 0;
}

int DMP_Read(uint8_t SlaveAddr, uint8_t readAddr, u16 NumByteToRead, uint8_t* pBuffer) {
	I2C_Software_StartSignal();
	
	I2C_Software_SendData(SlaveAddr<<1);
	I2C_Software_SendData(readAddr);
	
	
	I2C_Software_StartSignal();
	I2C_Software_SendData(SlaveAddr<<1 | 0x01);

	for (uint16_t i = 0; i < NumByteToRead; i++) {
		*(pBuffer + i) = I2C_Software_ReceiveByte();
		if (i == NumByteToRead-1) I2C_Software_SendAck(1);
		else I2C_Software_SendAck(0);
	}

	I2C_Software_StopSignal();
	return 0;
}

void MPU6050_Init(void) {
	long bias = 0;
	struct int_param_s *int_param;
	
	/* ��ȡ����ID�Ա��Ƿ���ȷ */
	uint8_t ReadID = 0x00;
	DMP_Read(MPU6050_ADDRESS, MPU6050_WHO_AM_I, 1, &ReadID);
	if(ReadID != MPU6050_ADDRESS) {
		NVIC_SystemReset();
	}
	
	/* DMP��ʼ�� */
	if(!mpu_init(int_param)) {
		if(!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL)) {
			//printf("mpu_set_sensor complete ......\r\n");
		}
		if(!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL)) {
			//printf("mpu_configure_fifo complete ......\r\n");
		}
		if(!mpu_set_sample_rate(IMU_DEFAULT_HZ)) {
			//printf("mpu_set_sample_rate complete ......\r\n");
		}
		if(!dmp_load_motion_driver_firmware()) {
			//printf("dmp_load_motion_driver_firmware complete ......\r\n");
		}
		if(!dmp_set_orientation(DMP_OrientationMatrix_2Scalar(gyro_orientation))) {
			//printf("dmp_set_orientation complete ......\r\n");
		}
		if(!dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
														DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | 
														DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL)) {
			//printf("dmp_enable_feature complete ......\r\n");
		}
		if(!dmp_set_fifo_rate(IMU_DEFAULT_HZ)) {
			 //printf("dmp_set_fifo_rate complete ......\r\n");
		}
		DMP_SelfTest();
		if(!mpu_set_dmp_state(0)) {
			 //printf("mpu_set_dmp_state complete ......\r\n");
		}
		if(!dmp_set_gyro_bias(&bias)) {
			 //printf("dmp_set_gyro_bias ......\r\n");
		}
		mpu_set_accel_fsr(4);
		mpu_set_gyro_fsr(500);
//		printf("dmp init complete\r\n");
	  }
	
#if MPU_Interrupt == 1
	MPU6050_INT_Init();
#endif
}

uint8_t MPU_DMP_ReadAngle(float *Pitch, float *Roll, float *Yaw) {
	uint8_t more;
	long quat[4];				// ��Ԫ��
	int16_t gyro[3], accel[3], sensors;
	unsigned long sensor_timestamp;	// ������ʱ���
	float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;
	
	if(dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more)) {
		return 1;	
	}
	
	if(sensors & 0x100) {
		q0 = quat[0]/q30;
		q1 = quat[1]/q30;
		q2 = quat[2]/q30;
		q3 = quat[3]/q30;
		
		/* ��Ԫ������ */
		*Pitch = asin(-2*q1*q3 + 2*q0*q2)* 57.3f;
		*Roll  = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3f;
		*Yaw   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3f;
		
		return 0;
	}	else {
		return 2;
	}
}

#endif

uint8_t MPU6050_GetID(void) {
	uint8_t ID;
	
//	I2C_Software_StartSignal();
//	I2C_Software_SendData(MPU6050_ADDRESS);
//	I2C_Software_SendData(MPU6050_WHO_AM_I);
//	
//	I2C_Software_StartSignal();
//	I2C_Software_SendData(MPU6050_ADDRESS | 0x01);
//	
//	ID = I2C_Software_ReceiveByte();
//	I2C_Software_SendAck(1);
//	I2C_Software_StopSignal();
	
	MPU6050_ReaData(MPU6050_WHO_AM_I, &ID, 1);
	
	return ID;
}

void MPU6050_READ(void) {
	static uint8_t original_data[14];
	
	// �������������ݵ�ַ�������˼��ٶȺ������ǹ�12�ֽ�
	MPU6050_ReaData(MPU6050_ACCEL_XOUTH, original_data, 14);
	
	// ��������������
	for(uint8_t i = 0; i < 3; i++)
		MPU6050_data[i] = ((original_data[2 * i] << 8) + original_data[2 * i + 1]);
	for(uint8_t i = 4; i < 7; i++)
		MPU6050_data[i - 1] = ((original_data[2 * i] << 8) + original_data[2 * i +1 ]);	
}

