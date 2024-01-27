#include "Motor.h"
#include "TIM2PWM.h"

void Motor_Init(void) {
	RCC_APB2PeriphClockCmd(Control_Periph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Control_Pin_1 | Control_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Control_Port, &GPIO_InitStructure);
	
	TIM2_PWM_Init(1000, 576, 0);
}

void Motor_SetState(enum MotorState state) {
	if (state == ForwardTurn) {
		GPIO_SetBits(Control_Port, GPIO_Pin_2);
		GPIO_ResetBits(Control_Port, GPIO_Pin_3);
	}
	else if (state == ReverseTurn) {
		GPIO_ResetBits(Control_Port, GPIO_Pin_2);
		GPIO_SetBits(Control_Port, GPIO_Pin_3);
	}
	else if (state == Stop) {
		GPIO_ResetBits(Control_Port, GPIO_Pin_2);
		GPIO_ResetBits(Control_Port, GPIO_Pin_3);
	}
}

void Motor_SetDutyCycle(int8_t DutyCycle) {
	TIM2_PWM2_SetCompare(DutyCycle);
}
