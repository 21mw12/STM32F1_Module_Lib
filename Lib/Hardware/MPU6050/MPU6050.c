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
  * @brief  MPU6050写数据
  * @param  writeAddr 寄存器地址
  * @param  data 要写入的数据
  * @retval 无
  */
void MPU6050_WriteData(uint8_t writeAddr, uint8_t data) {
	I2C_Software_StartSignal();
	I2C_Software_SendData(MPU6050_ADDRESS);
	I2C_Software_SendData(writeAddr);
	I2C_Software_SendData(data); 
	I2C_Software_StopSignal();
}

/**
  * @brief  MPU6050读数据
  * @param  writeAddr 寄存器地址
  * @param  dataArray 要读出的数据
  * @param  length 要读出的数量
  * @retval 无
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
  * @brief 硬件I2C等待事件
  * @param I2C_EVENT I2C事件 
  * @return 无
  */
void MPU6050_WaitEvent(uint32_t I2C_EVENT) {
	uint32_t To = Timeout;
	while (I2C_CheckEvent(I2CX, I2C_EVENT) != SUCCESS){
		To--;
		if (To == 0) {
			/* 超时的错误处理代码，可以添加到此处 */
			break;
		}
	}
}

void MPU6050_WriteData(uint8_t writeAddr, uint8_t data) {
	I2C_GenerateSTART(I2CX, ENABLE);										//硬件I2C生成起始条件
	MPU6050_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);					//等待EV5
	
	I2C_Send7bitAddress(I2CX, MPU6050_ADDRESS, I2C_Direction_Transmitter);	//硬件I2C发送从机地址，方向为发送
	MPU6050_WaitEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//等待EV6
	
	I2C_SendData(I2CX, writeAddr);											//硬件I2C发送寄存器地址
	MPU6050_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING);			//等待EV8
	
	I2C_SendData(I2CX, data);												//硬件I2C发送数据
	MPU6050_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//等待EV8_2
	
	I2C_GenerateSTOP(I2CX, ENABLE);											//硬件I2C生成终止条件
}

/* 读多个字节有BUG */
void MPU6050_ReaData(uint8_t readAddr, uint8_t* dataArray, uint16_t length) {	
	I2C_GenerateSTART(I2CX, ENABLE);										//硬件I2C生成起始条件
	MPU6050_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);					//等待EV5
	
	I2C_Send7bitAddress(I2CX, MPU6050_ADDRESS, I2C_Direction_Transmitter);	//硬件I2C发送从机地址，方向为发送
	MPU6050_WaitEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//等待EV6
	
	I2C_SendData(I2CX, readAddr);											//硬件I2C发送寄存器地址
	MPU6050_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//等待EV8_2
	
	I2C_GenerateSTART(I2CX, ENABLE);										//硬件I2C生成重复起始条件
	MPU6050_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);					//等待EV5
	
	I2C_Send7bitAddress(I2CX, MPU6050_ADDRESS, I2C_Direction_Receiver);		//硬件I2C发送从机地址，方向为接收
	MPU6050_WaitEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);		//等待EV6
	
	for (uint16_t i = 0; i < length; i++) {
		if (i + 1 == length) {
			I2C_AcknowledgeConfig(I2CX, DISABLE);									//在接收最后一个字节之前提前将应答失能
			I2C_GenerateSTOP(I2CX, ENABLE);											//在接收最后一个字节之前提前申请停止条件
		}
		
		MPU6050_WaitEvent(I2C_EVENT_MASTER_BYTE_RECEIVED);				//等待EV7
		*(dataArray + i) = I2C_ReceiveData(I2CX);											//接收数据寄存器
	}
	
	I2C_AcknowledgeConfig(I2CX, ENABLE);									//将应答恢复为使能，为了不影响后续可能产生的读取多字节操作
}
#endif

void MPU6050_Init(void) {
	MPU6050_WriteData(MPU6050_PWR_MGMT1, 0X01);  	// 取消睡眠模式，选择时钟源为X轴陀螺仪
	MPU6050_WriteData(MPU6050_PWR_MGMT2, 0X00); 	// 所有轴均不待机
	MPU6050_WriteData(MPU6050_SAMPLE_RATE, 0x09);	// 采样率分频寄存器，配置采样率
	MPU6050_WriteData(MPU6050_CFG, 0x06);					// 配置寄存器，配置DLPF
	MPU6050_WriteData(MPU6050_GYRO_CFG, 0x18);    // 陀螺仪配置寄存器，选择满量程为±2000°/s
	MPU6050_WriteData(MPU6050_ACCEL_CFG, 0x18);   // 加速度计配置寄存器，选择满量程为±16g
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
	
	// 读出连续的数据地址，包括了加速度和陀螺仪共12字节
	MPU6050_ReaData(MPU6050_ACCEL_XOUTH, original_data, 14);
	
	// 整合陀螺仪数据
	for(uint8_t i = 0; i < 3; i++)
		MPU6050_data[i] = ((original_data[2 * i] << 8) + original_data[2 * i + 1]);
	for(uint8_t i = 4; i < 7; i++)
		MPU6050_data[i - 1] = ((original_data[2 * i] << 8) + original_data[2 * i +1 ]);	
}

