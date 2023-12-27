#include "W25QXX.h"
#include "W25QXX_Register.h"
#include "delay.h"

void W25QXX_Init(void) {
  RCC_APB2PeriphClockCmd(W25QXX_GPIOPeriph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = W25QXX_CS_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(W25QXX_PORT, &GPIO_InitStructure);
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_SET);
}

void W25QXX_ReadID(uint8_t* MID, uint16_t* DID) {
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_RESET);	// 起始信号
	
	W25QXX_SwapByte(W25QXX_JEDEC_ID);
	
	*MID = W25QXX_SwapByte(W25QXX_DUMMY_BYTE);
	*DID = W25QXX_SwapByte(W25QXX_DUMMY_BYTE);
	*DID <<= 8;
	*DID |= W25QXX_SwapByte(W25QXX_DUMMY_BYTE);
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_SET);	// 结束信号
}

/**
  * @brief W25QXX写使能
  * @return 无
  */
void W25QXX_WriteEnable(void) {
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_RESET);	// 起始信号
	
	W25QXX_SwapByte(W25QXX_WRITE_ENABLE);
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_SET);	// 结束信号
}

/**
  * @brief W25QXX写失能
  * @return 无
  */
void W25QXX_WriteDisable(void) {
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_RESET);	// 起始信号
	
	W25QXX_SwapByte(W25QXX_WRITE_DISABLE);
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_SET);	// 结束信号
}

/**
  * @brief 等待芯片空闲
  * @return 无
  */
void W25QXX_WaitBusy(void) {
	uint32_t Timeout = 10000;
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_RESET);	// 起始信号
	
	W25QXX_SwapByte(W25QXX_READ_STATUS_REGISTER_1);
	while((W25QXX_SwapByte(W25QXX_DUMMY_BYTE) & 0x01) == 0x01) {
		Timeout--;
		if (Timeout == 0) {
			break;
		}
	}
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_SET);	// 结束信号
}

void W25QXX_RelieveWriteProtect(void) {
  W25QXX_WriteEnable();

	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_RESET);	// 起始信号
	
	W25QXX_SwapByte(W25QXX_WRITE_STATUS_REGISTER); // 发送写状态寄存器的指令
	W25QXX_SwapByte(0x00); 		// 写入状态寄存器1
	W25QXX_SwapByte(0x00); 		// 写入状态寄存器2
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_SET);	// 结束信号
	
	W25QXX_WaitBusy();
}

void W25QXX_WritePage(uint32_t address, uint8_t* dataArray, uint16_t count) {
	W25QXX_WriteEnable();
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_RESET);	// 起始信号
	
	W25QXX_SwapByte(W25QXX_PAGE_PROGRAM);
	
	W25QXX_SwapByte(address >> 16);
	W25QXX_SwapByte(address >> 8);
	W25QXX_SwapByte(address);
	
	for (uint16_t i = 0; i < count; i++) {
		W25QXX_SwapByte(dataArray[i]);
	}
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_SET);	// 结束信号
	
	W25QXX_WaitBusy();
}

void W25QXX_ReadPage(uint32_t address, uint8_t* dataArray, uint32_t count) {
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_RESET);	// 起始信号
	
	W25QXX_SwapByte(W25QXX_READ_DATA);
	
	W25QXX_SwapByte(address >> 16);
	W25QXX_SwapByte(address >> 8);
	W25QXX_SwapByte(address);
	
	for (uint32_t i = 0; i < count; i++) {
		dataArray[i] = W25QXX_SwapByte(W25QXX_DUMMY_BYTE);
	}
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_SET);	// 结束信号
}

void W25QXX_SectorErase(uint32_t address) {
	W25QXX_WriteEnable();
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_RESET);	// 起始信号
	
	W25QXX_SwapByte(W25QXX_SECTOR_ERASE_4KB);
	
	W25QXX_SwapByte(address >> 16);
	W25QXX_SwapByte(address >> 8);
	W25QXX_SwapByte(address);
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_SET);	// 结束信号
	W25QXX_WaitBusy();
}


void W25QXX_BlockErase(uint32_t address) {
	W25QXX_WriteEnable();
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_RESET);	// 起始信号
	
	W25QXX_SwapByte(W25QXX_BLOCK_ERASE_64KB);
	
	W25QXX_SwapByte(address >> 16);
	W25QXX_SwapByte(address >> 8);
	W25QXX_SwapByte(address);
	
	GPIO_WriteBit(W25QXX_PORT, W25QXX_CS_PIN, Bit_SET);	// 结束信号
	W25QXX_WaitBusy();
}
