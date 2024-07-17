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

int16_t MPU6050_data[6];

#if whichI2C == 0
/**
  * @brief  MPU6050д����
  * @param  writeAddr �Ĵ�����ַ
  * @param  data Ҫд�������
  * @retval ��
  */
void MPU6050_WriteData(uint8_t writeAddr, uint8_t data) {
	I2C_Software_StartSignal();
	I2C_Software_SendData(MPU6050_ADDRESS);
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
	I2C_Software_SendData(MPU6050_ADDRESS);
	I2C_Software_SendData(readAddr);
	
	I2C_Software_StartSignal();
	I2C_Software_SendData(MPU6050_ADDRESS | 0x01);
	
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

void MPU6050_Init(void) {
	MPU6050_WriteData(MPU6050_PWR_MGMT1, 0X01);  	// ȡ��˯��ģʽ��ѡ��ʱ��ԴΪX��������
	MPU6050_WriteData(MPU6050_PWR_MGMT2, 0X00); 	// �������������
	MPU6050_WriteData(MPU6050_SAMPLE_RATE, 0x09);	// �����ʷ�Ƶ�Ĵ��������ò�����
	MPU6050_WriteData(MPU6050_CFG, 0x06);					// ���üĴ���������DLPF
	MPU6050_WriteData(MPU6050_GYRO_CFG, 0x18);    // ���������üĴ�����ѡ��������Ϊ��2000��/s
	MPU6050_WriteData(MPU6050_ACCEL_CFG, 0x18);   // ���ٶȼ����üĴ�����ѡ��������Ϊ��16g
}

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

