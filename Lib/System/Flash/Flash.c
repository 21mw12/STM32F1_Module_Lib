#include "flash.h"

void FLASH_WriteWord(uint32_t Address, uint32_t Data) {
	FLASH_Unlock();
	FLASH_ProgramWord(Address, Data);
	FLASH_Lock();
}

void FLASH_WriteHalfWord(uint32_t Address, uint16_t Data) {
	FLASH_Unlock();
	FLASH_ProgramHalfWord(Address, Data);
	FLASH_Lock();
}

uint32_t FLASH_ReadWord(uint32_t Address) {
	return *((__IO uint32_t*)(Address));
}

uint16_t FLASH_ReadHalfWord(uint32_t Address) {
	return *((__IO uint16_t*)(Address));
}

uint8_t FLASH_ReadByte(uint32_t Address) {
	return *((__IO uint8_t*)(Address));
}

void FLASH_ClearAllPages(void) {
	FLASH_Unlock();
	FLASH_EraseAllPages();
	FLASH_Lock();
}

void FLASH_ClearPage(uint32_t PageAddress) {
	FLASH_Unlock();
	FLASH_ErasePage(PageAddress);
	FLASH_Lock();
}

uint16_t FLASH_GetSTM32_FLASHSIZE(void) {
	return *((__IO uint16_t*)(0x1FFFF7E0));
}

void FLASH_GetSTM32_ChipID(uint32_t* ChipID0, uint32_t* ChipID1, uint32_t* ChipID2) {
	*ChipID0 = *((__IO uint32_t*)(0x1FFFF7E8));
	*ChipID1 = *((__IO uint32_t*)(0x1FFFF7E8 + 0x04));
	*ChipID2 = *((__IO uint32_t*)(0x1FFFF7E8 + 0x08));
}
