#include "WDG.h"

void IWDG_Init(void) {
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);		// ���д����
	IWDG_SetPrescaler(IWDG_Prescaler_16);		// ����Ԥ��Ƶ
	IWDG_SetReload(IWDG_ARR);					// ������װֵ
	
	IWDG_ReloadCounter();		// ι��
	IWDG_Enable();
}

enum ResetStatus IWDG_isReset(void) {
	
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET) {
		RCC_ClearFlag();
		return Reset;		
	} else {
		return NoReset;
	}
}

void WWDG_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	// ����ʱ��
	
	WWDG_SetPrescaler(WWDG_Prescaler_8);			// ����Ԥ��Ƶ
	WWDG_SetWindowValue(0x40 | IWDG_WValue);	// д�����ô���ֵ W[5:0]
	WWDG_Enable(0x40 | IWDG_TValue);					//   д����ƼĴ��� T[5:0]
}

enum ResetStatus WWDG_isReset(void) {
	
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET) {
		RCC_ClearFlag();
		return Reset;		
	} else {
		return NoReset;
	}
}
