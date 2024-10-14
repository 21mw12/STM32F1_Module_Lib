#ifndef __MPU6050_REGISTER_H
#define __MPU6050_REGISTER_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�MPU6050��ؼĴ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/06/27
//
///////////////////////////////////////////////////////////

// MPU6050��ַ
#define MPU6050_ADDRESS					0x68
#define MPU6050_ADDRESS_AD			0x69	// AD0�����ڸߵ�ƽ�µĵ�ַ

// ��Դ����Ĵ���
#define MPU6050_PWR_MGMT1 			0X6B
#define MPU6050_PWR_MGMT2 			0X6C

// ����Ƶ�ʷ�Ƶ��
#define MPU6050_SAMPLE_RATE 		0X19

// �Լ�Ĵ���
#define MPU6050_SELF_TESTX 			0X0D	// �Լ�Ĵ���X
#define MPU6050_SELF_TESTY 			0X0E	// �Լ�Ĵ���Y
#define MPU6050_SELF_TESTZ 			0X0F	// �Լ�Ĵ���Z
#define MPU6050_SELF_TESTA 			0X10	// �Լ�Ĵ���A

// ���üĴ���
#define MPU6050_CFG 						0X1A
#define MPU6050_GYRO_CFG 				0X1B	// ���������üĴ���
#define MPU6050_ACCEL_CFG 			0X1C	// ���ٶȼ����üĴ���

// ���ٶ�ֵ�Ĵ���
#define MPU6050_ACCEL_XOUTH 		0X3B	// X���8λ�Ĵ���
#define MPU6050_ACCEL_XOUTL 		0X3C	// X���8λ�Ĵ���
#define MPU6050_ACCEL_YOUTH 		0X3D	// Y���8λ�Ĵ���
#define MPU6050_ACCEL_YOUTL 		0X3E	// Y���8λ�Ĵ���
#define MPU6050_ACCEL_ZOUTH 		0X3F	// Z���8λ�Ĵ���
#define MPU6050_ACCEL_ZOUTL 		0X40	// Z���8λ�Ĵ���

// ������ֵ�Ĵ���
#define MPU6050_GYRO_XOUTH 			0X43	// X���8λ�Ĵ���
#define MPU6050_GYRO_XOUTL 			0X44	// X���8λ�Ĵ���
#define MPU6050_GYRO_YOUTH 			0X45	// Y���8λ�Ĵ���
#define MPU6050_GYRO_YOUTL 			0X46	// Y���8λ�Ĵ���
#define MPU6050_GYRO_ZOUTH 			0X47	// Z���8λ�Ĵ���
#define MPU6050_GYRO_ZOUTL 			0X48	// Z���8λ�Ĵ���

// �¶�ֵ�Ĵ���
#define MPU6050_TEMP_OUTH 			0X41	// ��8λ�Ĵ���
#define MPU6050_TEMP_OUTL 			0X42	// ��8λ�Ĵ���

// who am i �Ĵ���
#define MPU6050_WHO_AM_I 				0X75

#define MPU6050_MOTION_DET 		0X1F	//�˶���ֵⷧ���üĴ���
#define MPU6050_FIFO_EN 			0X23	//FIFOʹ�ܼĴ���
#define MPU6050_I2CMST_CTRL 		0X24	//IIC�������ƼĴ���
#define MPU6050_I2CSLV0_ADDR 	0X25	//IIC�ӻ�0������ַ�Ĵ���
#define MPU6050_I2CSLV0 			0X26	//IIC�ӻ�0���ݵ�ַ�Ĵ���
#define MPU6050_I2CSLV0_CTRL 	0X27	//IIC�ӻ�0���ƼĴ���
#define MPU6050_I2CSLV1_ADDR 	0X28	//IIC�ӻ�1������ַ�Ĵ���
#define MPU6050_I2CSLV1 			0X29	//IIC�ӻ�1���ݵ�ַ�Ĵ���
#define MPU6050_I2CSLV1_CTRL 	0X2A	//IIC�ӻ�1���ƼĴ���
#define MPU6050_I2CSLV2_ADDR 	0X2B	//IIC�ӻ�2������ַ�Ĵ���
#define MPU6050_I2CSLV2 			0X2C	//IIC�ӻ�2���ݵ�ַ�Ĵ���
#define MPU6050_I2CSLV2_CTRL 	0X2D	//IIC�ӻ�2���ƼĴ���
#define MPU6050_I2CSLV3_ADDR 	0X2E	//IIC�ӻ�3������ַ�Ĵ���
#define MPU6050_I2CSLV3 			0X2F	//IIC�ӻ�3���ݵ�ַ�Ĵ���
#define MPU6050_I2CSLV3_CTRL 	0X30	//IIC�ӻ�3���ƼĴ���
#define MPU6050_I2CSLV4_ADDR 	0X31	//IIC�ӻ�4������ַ�Ĵ���
#define MPU6050_I2CSLV4 			0X32	//IIC�ӻ�4���ݵ�ַ�Ĵ���
#define MPU6050_I2CSLV4_DO 		0X33	//IIC�ӻ�4д���ݼĴ���
#define MPU6050_I2CSLV4_CTRL 	0X34	//IIC�ӻ�4���ƼĴ���
#define MPU6050_I2CSLV4_DI 		0X35	//IIC�ӻ�4�����ݼĴ���


#define MPU6050_I2CMST_STA		0X36	//IIC����״̬�Ĵ���
#define MPU6050_INTBP_CFG		0X37	//�ж�/��·���üĴ���
#define MPU6050_INT_EN			0X38	//�ж�ʹ�ܼĴ���
#define MPU6050_INT_STA			0X3A	//�ж�״̬�Ĵ���

#define MPU6050_I2CMST_DELAY 	0X67	//IIC������ʱ����Ĵ���
#define MPU6050_SIGPATH_RST 		0X68	//�ź�ͨ����λ�Ĵ���
#define MPU6050_MDETECT_CTRL 	0X69	//�˶������ƼĴ���
#define MPU6050_USER_CTRL 		0X6A	//�û����ƼĴ���
#define MPU6050_PWR_MGMT1 		0X6B	//��Դ����Ĵ���1
#define MPU6050_PWR_MGMT2 		0X6C	//��Դ����Ĵ���2 
#define MPU6050_FIFO_CNTH 		0X72	//FIFO�����Ĵ����߰�λ
#define MPU6050_FIFO_CNTL 		0X73	//FIFO�����Ĵ����Ͱ�λ
#define MPU6050_FIFO_RW 			0X74	//FIFO��д�Ĵ���
#define MPU6050_DEVICE_ID 		0X75	//����ID�Ĵ���


#endif
