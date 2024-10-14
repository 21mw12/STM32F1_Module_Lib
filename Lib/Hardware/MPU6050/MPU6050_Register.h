#ifndef __MPU6050_REGISTER_H
#define __MPU6050_REGISTER_H

///////////////////////////////////////////////////////////
//
// 文件功能：MPU6050相关寄存器
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/06/27
//
///////////////////////////////////////////////////////////

// MPU6050地址
#define MPU6050_ADDRESS					0x68
#define MPU6050_ADDRESS_AD			0x69	// AD0引脚在高电平下的地址

// 电源管理寄存器
#define MPU6050_PWR_MGMT1 			0X6B
#define MPU6050_PWR_MGMT2 			0X6C

// 采样频率分频器
#define MPU6050_SAMPLE_RATE 		0X19

// 自检寄存器
#define MPU6050_SELF_TESTX 			0X0D	// 自检寄存器X
#define MPU6050_SELF_TESTY 			0X0E	// 自检寄存器Y
#define MPU6050_SELF_TESTZ 			0X0F	// 自检寄存器Z
#define MPU6050_SELF_TESTA 			0X10	// 自检寄存器A

// 配置寄存器
#define MPU6050_CFG 						0X1A
#define MPU6050_GYRO_CFG 				0X1B	// 陀螺仪配置寄存器
#define MPU6050_ACCEL_CFG 			0X1C	// 加速度计配置寄存器

// 加速度值寄存器
#define MPU6050_ACCEL_XOUTH 		0X3B	// X轴高8位寄存器
#define MPU6050_ACCEL_XOUTL 		0X3C	// X轴低8位寄存器
#define MPU6050_ACCEL_YOUTH 		0X3D	// Y轴高8位寄存器
#define MPU6050_ACCEL_YOUTL 		0X3E	// Y轴低8位寄存器
#define MPU6050_ACCEL_ZOUTH 		0X3F	// Z轴高8位寄存器
#define MPU6050_ACCEL_ZOUTL 		0X40	// Z轴低8位寄存器

// 陀螺仪值寄存器
#define MPU6050_GYRO_XOUTH 			0X43	// X轴高8位寄存器
#define MPU6050_GYRO_XOUTL 			0X44	// X轴低8位寄存器
#define MPU6050_GYRO_YOUTH 			0X45	// Y轴高8位寄存器
#define MPU6050_GYRO_YOUTL 			0X46	// Y轴低8位寄存器
#define MPU6050_GYRO_ZOUTH 			0X47	// Z轴高8位寄存器
#define MPU6050_GYRO_ZOUTL 			0X48	// Z轴低8位寄存器

// 温度值寄存器
#define MPU6050_TEMP_OUTH 			0X41	// 高8位寄存器
#define MPU6050_TEMP_OUTL 			0X42	// 低8位寄存器

// who am i 寄存器
#define MPU6050_WHO_AM_I 				0X75

#define MPU6050_MOTION_DET 		0X1F	//运动检测阀值设置寄存器
#define MPU6050_FIFO_EN 			0X23	//FIFO使能寄存器
#define MPU6050_I2CMST_CTRL 		0X24	//IIC主机控制寄存器
#define MPU6050_I2CSLV0_ADDR 	0X25	//IIC从机0器件地址寄存器
#define MPU6050_I2CSLV0 			0X26	//IIC从机0数据地址寄存器
#define MPU6050_I2CSLV0_CTRL 	0X27	//IIC从机0控制寄存器
#define MPU6050_I2CSLV1_ADDR 	0X28	//IIC从机1器件地址寄存器
#define MPU6050_I2CSLV1 			0X29	//IIC从机1数据地址寄存器
#define MPU6050_I2CSLV1_CTRL 	0X2A	//IIC从机1控制寄存器
#define MPU6050_I2CSLV2_ADDR 	0X2B	//IIC从机2器件地址寄存器
#define MPU6050_I2CSLV2 			0X2C	//IIC从机2数据地址寄存器
#define MPU6050_I2CSLV2_CTRL 	0X2D	//IIC从机2控制寄存器
#define MPU6050_I2CSLV3_ADDR 	0X2E	//IIC从机3器件地址寄存器
#define MPU6050_I2CSLV3 			0X2F	//IIC从机3数据地址寄存器
#define MPU6050_I2CSLV3_CTRL 	0X30	//IIC从机3控制寄存器
#define MPU6050_I2CSLV4_ADDR 	0X31	//IIC从机4器件地址寄存器
#define MPU6050_I2CSLV4 			0X32	//IIC从机4数据地址寄存器
#define MPU6050_I2CSLV4_DO 		0X33	//IIC从机4写数据寄存器
#define MPU6050_I2CSLV4_CTRL 	0X34	//IIC从机4控制寄存器
#define MPU6050_I2CSLV4_DI 		0X35	//IIC从机4读数据寄存器


#define MPU6050_I2CMST_STA		0X36	//IIC主机状态寄存器
#define MPU6050_INTBP_CFG		0X37	//中断/旁路设置寄存器
#define MPU6050_INT_EN			0X38	//中断使能寄存器
#define MPU6050_INT_STA			0X3A	//中断状态寄存器

#define MPU6050_I2CMST_DELAY 	0X67	//IIC主机延时管理寄存器
#define MPU6050_SIGPATH_RST 		0X68	//信号通道复位寄存器
#define MPU6050_MDETECT_CTRL 	0X69	//运动检测控制寄存器
#define MPU6050_USER_CTRL 		0X6A	//用户控制寄存器
#define MPU6050_PWR_MGMT1 		0X6B	//电源管理寄存器1
#define MPU6050_PWR_MGMT2 		0X6C	//电源管理寄存器2 
#define MPU6050_FIFO_CNTH 		0X72	//FIFO计数寄存器高八位
#define MPU6050_FIFO_CNTL 		0X73	//FIFO计数寄存器低八位
#define MPU6050_FIFO_RW 			0X74	//FIFO读写寄存器
#define MPU6050_DEVICE_ID 		0X75	//器件ID寄存器


#endif
