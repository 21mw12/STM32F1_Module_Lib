#include "WDG.h"

void IWDG_Init(void) {
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);		// 解除写保护
	IWDG_SetPrescaler(IWDG_Prescaler_16);		// 配置预分频
	IWDG_SetReload(IWDG_ARR);					// 配置重装值
	
	IWDG_ReloadCounter();		// 喂狗
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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	// 开启时钟
	
	WWDG_SetPrescaler(WWDG_Prescaler_8);			// 配置预分频
	WWDG_SetWindowValue(0x40 | IWDG_WValue);	// 写入配置窗口值 W[5:0]
	WWDG_Enable(0x40 | IWDG_TValue);					//   写入控制寄存器 T[5:0]
}

enum ResetStatus WWDG_isReset(void) {
	
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET) {
		RCC_ClearFlag();
		return Reset;		
	} else {
		return NoReset;
	}
}
