#include "LOWPOWER.h"

void LowerPower_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
}

void LowerPower_EnterStop(void) {
	PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
	SystemInit();
}

void LowerPower_EnterSandBY(void) {
	
	/* 进入待机模式前要将所有外设全部关闭 */
	/* 可由软件配合硬件执行，并插入才此 */
	
	PWR_EnterSTANDBYMode();
}

void LowerPower_SandBY_WakeUpPin_Init(void) {
	PWR_WakeUpPinCmd(ENABLE);
}
