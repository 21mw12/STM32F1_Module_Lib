#include "KLM.h"

void KLM_Struct_Init(KLM_Struct* klm, float Q_Set, float R_Set) {
	klm->P = 1;
	klm->P_ = 0;
	klm->X = 1;
	klm->X_ = 0;
	klm->K = 0;
	klm->Q = Q_Set;
	klm->R = R_Set;
}

float KalmanFilter(KLM_Struct* klm, float Z) {
    klm->X_ = klm->X + 0;
    klm->P_ = klm->P + klm->Q;
    klm->K = klm->P_ / (klm->P_ + klm->R);
    klm->X = klm->X_ + klm->K * (Z - klm->X_);
    klm->P = klm->P_ - klm->K * klm->P_;
    return klm->X;
}