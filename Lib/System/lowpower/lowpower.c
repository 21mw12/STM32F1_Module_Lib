#include "LOWPOWER.h"

void LowerPower_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
}

void LowerPower_EnterStop(void) {
	PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
	SystemInit();
}

void LowerPower_EnterSandBY(void) {
	
	/* �������ģʽǰҪ����������ȫ���ر� */
	/* ����������Ӳ��ִ�У�������Ŵ� */
	
	PWR_EnterSTANDBYMode();
}

void LowerPower_SandBY_WakeUpPin_Init(void) {
	PWR_WakeUpPinCmd(ENABLE);
}
