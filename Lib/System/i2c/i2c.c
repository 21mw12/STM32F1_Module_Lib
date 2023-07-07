#include "i2c.h"
#include "i2c_software.h"
#include "i2c_hardware.h"

void I2C_Bus_Init(void) {
	if (SoftOrHaradWareI2C == 0) {
		I2C_Software_Init();
	} else {
		I2C_Hardware_Init();
	}
}

void I2C_Bus_SendByte(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t pBuffer) {
	if (SoftOrHaradWareI2C == 0) {
		I2C_Software_SendByte(SlaveAddr, writeAddr, pBuffer);
	} else {
		I2C_Hardware_SendByte(SlaveAddr, writeAddr, pBuffer);
	}
}

void I2C_Bus_SendArray(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t* pBuffer, uint16_t NumByteToWrite) {
	if (SoftOrHaradWareI2C == 0) {
		I2C_Software_SendArray(SlaveAddr, writeAddr, pBuffer, NumByteToWrite);
	} else {
		I2C_Hardware_SendArray(SlaveAddr, writeAddr, pBuffer, NumByteToWrite);
	}
}

uint8_t I2C_Bus_ReadByte(uint8_t SlaveAddr, uint8_t readAddr) {
	if (SoftOrHaradWareI2C == 0) {
		return I2C_Software_ReadByte(SlaveAddr, readAddr);
	} else {
		return I2C_Hardware_ReadByte(SlaveAddr, readAddr);
	}
}

uint8_t I2C_Bus_ReadArray(uint8_t SlaveAddr, uint8_t readAddr, uint8_t* pBuffer, uint16_t NumByteToRead) {
	uint8_t error = 1;
	
	if (SoftOrHaradWareI2C == 0) {
		I2C_Software_ReadArray(SlaveAddr, readAddr, pBuffer, NumByteToRead);
	} else {
		error = I2C_Hardware_ReadArray(SlaveAddr, readAddr, pBuffer, NumByteToRead);
	}
	return error;
}
