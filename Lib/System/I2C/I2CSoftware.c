#include "I2CSoftware.h"

///////////////////////////////////////////////////////////
//
// I2C基础时序实现
//
///////////////////////////////////////////////////////////

/**
  * @brief  SCL写数据
  * @param  state ： 数据内容
  * @retval 无
  */
void SCL_Write(uint8_t state) {
	GPIO_WriteBit(I2C_Software_PORT, I2C_Software_SCL_PIN, (BitAction)state);
}

/**
  * @brief  SDA写数据
  * @param  state ： 数据内容
  * @retval 无
  */
void SDA_Write(uint8_t state) {
	GPIO_WriteBit(I2C_Software_PORT, I2C_Software_SDA_PIN, (BitAction)state);
}

/**
  * @brief  SDA读数据
  * @retval 读取到的数据
  */
uint8_t SDA_Read(void) {
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(I2C_Software_PORT, I2C_Software_SDA_PIN);
    Delay_us(10);
    return BitValue;
}

/**
  * @brief  I2C开始
  * @param  GPIOx ： IO端口组
  * @param  GPIO_Pin ： IO端口
  * @retval 无
  */
void I2C_Start(void) {
	SDA_Write(1);
	SCL_Write(1);
	SDA_Write(0);
	SCL_Write(0);
}

/**
  * @brief  I2C停止
  * @param  GPIOx ： IO端口组
  * @param  GPIO_Pin ： IO端口
  * @retval 无
  */
void I2C_Stop(void) {
	SDA_Write(0);
	SCL_Write(1);
	SDA_Write(1);
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
  */
void I2C_SendByte(uint8_t Byte) {
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		SDA_Write(Byte & (0x80 >> i));
		SCL_Write(1);
		SCL_Write(0);
	}
	SCL_Write(1);	//额外的一个时钟，不处理应答信号
	SCL_Write(0);
}

/**
  * @brief  I2C接收一个字节
  * @retval 接收到的数据
  */
uint8_t I2C_ReceiveByte(void) {
    uint8_t i;
    uint8_t Byte = 0x00;
    SDA_Write(1);
    for (i = 0; i < 8; i++) {
        SCL_Write(1);
        if (SDA_Read() == 1) {
            Byte |= (0x80 >> i);
        }
        SCL_Write(0);
    }
    return Byte;
}

/**
  * @brief  发送应答
  * @param  应答信息
  * @retval 无
  */
void I2C_SendAck(uint8_t AckBit) {
    SDA_Write(AckBit);
    SCL_Write(1);
    SCL_Write(0);
}

/**
  * @brief  接收应答
  * @retval 应答信息
  */
uint8_t I2C_ReceiveAck(void) {
    uint8_t AckBit;
    SDA_Write(1);
    SCL_Write(1);
    AckBit = SDA_Read();
    SCL_Write(0);
    return AckBit;
}

///////////////////////////////////////////////////////////
//
// I2C基础功能实现
//
///////////////////////////////////////////////////////////

void I2C_Software_Init(void) {
  RCC_APB2PeriphClockCmd(I2C_Software_GPIOPeriph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = I2C_Software_SCL_PIN | I2C_Software_SDA_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(I2C_Software_PORT, &GPIO_InitStructure);
	
	SCL_Write(1);
	SDA_Write(1);
}

void I2C_Software_SendByte(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t pBuffer) {
	I2C_Start();
	I2C_SendByte(SlaveAddr);
	I2C_SendByte(writeAddr);
	I2C_SendByte(pBuffer); 
	I2C_Stop();
}

void I2C_Software_SendArray(uint8_t SlaveAddr, uint8_t WriteAddr, uint8_t* pBuffer, u16 NumByteToWrite) {
	I2C_Start();
	I2C_SendByte(SlaveAddr);
	I2C_SendByte(WriteAddr);
	
	for (uint16_t i = 0; i < NumByteToWrite; i++) {
		I2C_SendByte(*(pBuffer + i)); 
	}
	
	I2C_Stop();
}

uint8_t I2C_Software_ReadByte(uint8_t SlaveAddr, uint8_t readAddr) {
	uint8_t data;

	I2C_Start();
	I2C_SendByte(SlaveAddr);
	I2C_SendByte(readAddr);
	data = I2C_ReceiveByte();
	I2C_Stop();

	return data;
}

void I2C_Software_ReadArray(uint8_t SlaveAddr, uint8_t readAddr, uint8_t* pBuffer, u16 NumByteToRead) {
	I2C_Start();
	I2C_SendByte(SlaveAddr);
	I2C_SendByte(readAddr);

	for (uint16_t i = 0; i < NumByteToRead; i++) {
		*(pBuffer + i) = I2C_ReceiveByte();
	}

	I2C_Stop();
}
