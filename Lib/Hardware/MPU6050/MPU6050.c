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
  * @brief  MPU6050中断引脚初始化
  * @retval 无
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
  * @brief  MPU6050写数据
  * @param  writeAddr 寄存器地址
  * @param  data 要写入的数据
  * @retval 无
  */
void MPU6050_WriteData(uint8_t writeAddr, uint8_t data) {
	I2C_Software_StartSignal();
	I2C_Software_SendData(MPU6050_ADDRESS << 1);
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

#if useDMP == 0

void MPU6050_Init(void) {
	MPU6050_WriteData(MPU6050_PWR_MGMT1, 0X01);  	// 取消睡眠模式，选择时钟源为X轴陀螺仪
	MPU6050_WriteData(MPU6050_PWR_MGMT2, 0X00); 	// 所有轴均不待机
	MPU6050_WriteData(MPU6050_SAMPLE_RATE, 0x09);	// 采样率分频寄存器，配置采样率
	MPU6050_WriteData(MPU6050_CFG, 0x06);					// 配置寄存器，配置DLPF
	MPU6050_WriteData(MPU6050_GYRO_CFG, 0x18);    // 陀螺仪配置寄存器，选择满量程为±2000°/s
	MPU6050_WriteData(MPU6050_ACCEL_CFG, 0x18);   // 加速度计配置寄存器，选择满量程为±16g
	
#if MPU_Interrupt == 1
	MPU6050_INT_Init();
#endif
}

#else
// 用于四元数缩放
#define q30  1073741824.0f
// 定义陀螺仪的初始方向
static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};

/**
  * @brief  传感器自检，设置DMP的偏置
  * @retval 无
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
  * @brief  将行向量转换为符号模式
  * @retval 符号模式
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
  * @brief  将方位矩阵转换为符号模式
  * @retval 符号模式
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
	
	/* 读取器件ID对比是否正确 */
	uint8_t ReadID = 0x00;
	DMP_Read(MPU6050_ADDRESS, MPU6050_WHO_AM_I, 1, &ReadID);
	if(ReadID != MPU6050_ADDRESS) {
		NVIC_SystemReset();
	}
	
	/* DMP初始化 */
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
	long quat[4];				// 四元数
	int16_t gyro[3], accel[3], sensors;
	unsigned long sensor_timestamp;	// 传感器时间戳
	float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;
	
	if(dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more)) {
		return 1;	
	}
	
	if(sensors & 0x100) {
		q0 = quat[0]/q30;
		q1 = quat[1]/q30;
		q2 = quat[2]/q30;
		q3 = quat[3]/q30;
		
		/* 四元数解算 */
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
	
	// 读出连续的数据地址，包括了加速度和陀螺仪共12字节
	MPU6050_ReaData(MPU6050_ACCEL_XOUTH, original_data, 14);
	
	// 整合陀螺仪数据
	for(uint8_t i = 0; i < 3; i++)
		MPU6050_data[i] = ((original_data[2 * i] << 8) + original_data[2 * i + 1]);
	for(uint8_t i = 4; i < 7; i++)
		MPU6050_data[i - 1] = ((original_data[2 * i] << 8) + original_data[2 * i +1 ]);	
}

