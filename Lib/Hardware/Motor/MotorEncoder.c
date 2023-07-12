#include "MotorEncoder.h"

void MotorEncoder_Init(void) {
	RCC_APB2PeriphClockCmd(Control_Periph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Control_PIN_1 | Control_PIN_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Control_PORT, &GPIO_InitStructure);
	
	TIM3_Encoder_Init();
	TIM2_PWM_Init(1000, 576, 0);
}

void MotorEncoder_SetState(enum MotorState state) {
	if (state == ForwardTurn) {
		GPIO_SetBits(Control_PORT, GPIO_Pin_2);
		GPIO_ResetBits(Control_PORT, GPIO_Pin_3);
	}
	else if (state == ReverseTurn) {
		GPIO_ResetBits(Control_PORT, GPIO_Pin_2);
		GPIO_SetBits(Control_PORT, GPIO_Pin_3);
	}
	else if (state == Stop) {
		GPIO_ResetBits(Control_PORT, GPIO_Pin_2);
		GPIO_ResetBits(Control_PORT, GPIO_Pin_3);
	}
}

void MotorEncoder_SetDutyCycle(int8_t DutyCycle) {
	TIM2_PWM2_SetCompare(DutyCycle);
}

float MotorEncoder_CalculateSpeed(void) {
	int16_t EncoderCount = TIM3_Encoder_GetClear();
	// ��̥ת�˵�Ȧ�� = ��ǰ����ֵ / (���ֱ� * תһȦ����ֵ)
	// �ٶ� = ��̥ת�˵�Ȧ�� * ��̥�ܳ� / ������ʱ��
	float speed = (EncoderCount / (float) (Gear_Ratio * HoareEncoder_Circle_Count)) * Tyre_Perimeter / Calculate_Time;	// ������̥ת�˼�Ȧ
	return speed;
}

