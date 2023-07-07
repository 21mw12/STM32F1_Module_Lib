#include "MPU6050.h"

// X、Y、Z三轴加速度/陀螺仪原始数据
// 从下标0到5分别是： AX、 AY、 AZ、 GX、 GY、 GZ
uint16_t MPU6050_data[5];

/**
  * @brief  MPU6050写数据
  * @param  writeAddr 寄存器地址
  * @param  data 要写入的数据
  * @retval 无
  */
void MPU6050_WriteData(uint8_t writeAddr, uint8_t data) {
	I2C_Bus_SendByte(MPU6050_ADDRESS, writeAddr, data);
}

/**
  * @brief  MPU6050读数据
  * @param  writeAddr 寄存器地址
  * @param  dataArray 要读出的数据
  * @param  length 要读出的数量
  * @retval 无
  */
void MPU6050_ReaData(uint8_t writeAddr, uint8_t* dataArray, uint16_t length) {
	I2C_Bus_ReadArray(MPU6050_ADDRESS, writeAddr, dataArray, length);
}

/**
  * @brief 	设置MPU6050陀螺仪传感器满量程范围
  * @param 	fsr 陀螺仪传感器满量程范围
	* 						0 ： ±250dps
	* 						1 ： ±500dps
	* 						2 ： ±1000dps
	* 						3 ： ±2000dps
  * @return 无
  */
void MPU6050_Set_Gyro_Fsr(uint8_t fsr) {
	MPU6050_WriteData(MPU6050_GYRO_CFG, fsr<<3);
}

/**
  * @brief 	设置MPU6050陀螺仪传感器满量程范围
  * @param 	fsr 加速度传感器满量程范围
	* 						0 ： ±2g
	* 						1 ： ±4g
	* 						2 ： ±8g
	* 						3 ： ±16g
  * @return 无
  */
void MPU6050_Set_Accel_Fsr(uint8_t fsr) {
	MPU6050_WriteData(MPU6050_ACCEL_CFG, fsr<<3);
}

/**
  * @brief 	设置MPU6050数字低通滤波器
  * @param 	lpf 数字低通滤波频率(Hz)
  * @return 无
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
  * @brief 	设置MPU6050数字低通滤波器(假定Fs=1KHz)
  * @param 	rate 采样率（4~1000Hz）
  * @return 无
  */
void MPU6050_Set_Rate(uint16_t rate) {
	uint8_t data;
	if (rate > 1000) rate = 1000;
	if (rate < 4) rate = 4;
	data = 1000 / rate - 1;
	
	MPU6050_WriteData(MPU6050_SAMPLE_RATE, data);
 	MPU6050_Set_LPF(rate / 2);	// 自动设置LPF为采样率的一半
}


void MPU6050_Init(void) {	
	uint8_t res;
	
	MPU6050_WriteData(MPU6050_PWR_MGMT1, 0X80);		// 复位MPU6050
  Delay_ms(100);
	MPU6050_WriteData(MPU6050_PWR_MGMT1, 0X00);		// 唤醒MPU6050
	MPU6050_Set_Gyro_Fsr(3);											// 陀螺仪传感器,±2000dps
	MPU6050_Set_Accel_Fsr(0);											// 加速度传感器,±2g
	MPU6050_Set_Rate(50);													// 设置采样率50Hz
	MPU6050_WriteData(MPU6050_INT_EN, 0X00);			// 关闭所有中断
	MPU6050_WriteData(MPU6050_USER_CTRL, 0X00);		// I2C主模式关闭
	MPU6050_WriteData(MPU6050_FIFO_EN, 0X00);			// 关闭FIFO
	MPU6050_WriteData(MPU6050_INTBP_CFG, 0X80);		// INT引脚低电平有效

	MPU6050_ReaData(MPU6050_DEVICE_ID, &res, 1);

	if(res == MPU6050_ADDRESS) {
		MPU6050_WriteData(MPU6050_PWR_MGMT1, 0X01);	// 设置CLKSEL,PLL X轴为参考
		MPU6050_WriteData(MPU6050_PWR_MGMT2, 0X00);	// 加速度与陀螺仪都工作
		MPU6050_Set_Rate(50);												// 设置采样率为50Hz
 	}
}

uint8_t MPU6050_GetID(void) {
	uint8_t ID;
	MPU6050_ReaData(MPU6050_WHO_AM_I, &ID, 1);
	return ID;
}

void MPU6050_READ(void) {
	uint8_t original_data[14];
	
	// 读出连续的数据地址，包括了加速度和陀螺仪共12字节
	MPU6050_ReaData(MPU6050_ACCEL_XOUTH, original_data, 14);
	
	// 整合陀螺仪数据
	for(uint8_t i = 0; i < 3; i++)
		MPU6050_data[i] = ((original_data[2 * i] << 8) + original_data[2 * i + 1]);
	for(uint8_t i = 4; i < 7; i++)
		MPU6050_data[i - 1] = ((original_data[2 * i] << 8) + original_data[2 * i +1 ]);        
}

