#include "SecondChronograph.h"

void SecondChronograph_ExchangeWorkState(SecondChronograph* sClock) {
	Clock_ExchangeWorkState(&sClock->cTime);
}

void SecondChronograph_HeartBeat(SecondChronograph* sClock) {
	if (sClock->cTime.cTimeState == cTimeState_Working) {
		if (Clock_IncreaseTime(&sClock->cTime) == cTimeState_Idel) {
			sClock->cTime.cTimeState = cTimeState_Idel;
		}
	}
}

void SecondChronograph_ClearTime(SecondChronograph* sClock) {
	sClock->cTime.hour = 0;
	sClock->cTime.minute = 0;
	sClock->cTime.second = 0;
}
