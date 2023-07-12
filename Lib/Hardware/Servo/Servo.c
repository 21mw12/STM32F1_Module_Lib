#include "Servo.h"

void Servo_Init(void) {
	TIM2_PWM_Init(7200, 200, 0);
}

void Servo_SetAngle(float Angle) {
	// ����Ƕ�0~180��Ӧ��ƽ��ת�Ƚ�ֵ0~960
	// ֱ�ӵı�����ϵΪ5.333...
	TIM2_PWM1_SetCompare(Angle * 5.333);
}