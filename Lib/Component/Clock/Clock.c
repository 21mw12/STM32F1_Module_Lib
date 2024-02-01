#include "Clock.h"

void Clock_ExchangeWorkState(ClockTime* cTime) {
	if (cTime->cTimeState == cTimeState_Idel) {
		cTime->cTimeState = cTimeState_Working;
	} else {
		cTime->cTimeState = cTimeState_Idel;	
	}	
}

ClockTimeState Clock_ReduceTime(ClockTime* cTime) {
	if (cTime->second == 0) {
		if (cTime->minute == 0) {
			if (cTime->hour == 0) {
				return cTimeState_Idel;
			} else {
				cTime->hour--;
				cTime->minute = 59;
				cTime->second = 59;
			}
		} else {
			cTime->minute--;
			cTime->second = 59;
		}
	} else {
		cTime->second--;
	}
	return cTimeState_Working;
}

ClockTimeState Clock_IncreaseTime(ClockTime* cTime) {
	cTime->second++;
	if (cTime->second == 60) {
		cTime->minute++;
		cTime->second = 0;
		if (cTime->minute == 60) {
			cTime->hour++;
			cTime->minute = 0;
			if (cTime->hour == 24) {
				return cTimeState_Idel;
			}
		}
	}
	return cTimeState_Working;
}

