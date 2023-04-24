#include "i2c.h"

void SCL_Write(uint8_t state) {
	GPIO_WriteBit(I2C_PORT, SCL_PIN, (BitAction)state);
}

void SDA_Write(uint8_t state) {
	GPIO_WriteBit(I2C_PORT, SDA_PIN, (BitAction)state);
}

uint8_t SDA_Read(void) {
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(I2C_PORT, SDA_PIN);
    Delay_us(10);
    return BitValue;
}

void I2C_Start(void) {
	SDA_Write(1);
	SCL_Write(1);
	SDA_Write(0);
	SCL_Write(0);
}

void I2C_Stop(void) {
	SDA_Write(0);
	SCL_Write(1);
	SDA_Write(1);
}

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

void I2C_SendAck(uint8_t AckBit) {
    SDA_Write(AckBit);
    SCL_Write(1);
    SCL_Write(0);
}

uint8_t I2C_ReceiveAck(void) {
    uint8_t AckBit;
    SDA_Write(1);
    SCL_Write(1);
    AckBit = SDA_Read();
    SCL_Write(0);
    return AckBit;
}
