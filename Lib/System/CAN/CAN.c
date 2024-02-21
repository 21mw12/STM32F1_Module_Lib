#include "CAN.h"

uint8_t CAN1_RxPacket[8] = {0x00};

void CAN1_Init(void) {
	/* ��ʼ��ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	/* ��ʼ������ */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* ��ʼ��CAN */	
	CAN_InitTypeDef CAN_InitStructure;	
	CAN_InitStructure.CAN_TTCM = DISABLE;   // ��ʱ�䴥��ͨ��ģʽ   
	CAN_InitStructure.CAN_ABOM = DISABLE;   // ����Զ����߹���	  
	CAN_InitStructure.CAN_AWUM = DISABLE;   // ˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
	CAN_InitStructure.CAN_NART = ENABLE;   	// ��ʹ�ñ����Զ����� 
	CAN_InitStructure.CAN_RFLM = DISABLE;   // ���Ĳ�����,�µĸ��Ǿɵ�  
	CAN_InitStructure.CAN_TXFP = DISABLE;   // ���ȼ��ɱ��ı�ʶ������ 
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;   //CAN����ģʽ���� 
	CAN_InitStructure.CAN_SJW = SWJ;   			// ����ͬ����Ծ���Ϊtsjw+1��ʱ�䵥λ
	CAN_InitStructure.CAN_BS1 = BS1;
	CAN_InitStructure.CAN_BS2 = BS2;
	CAN_InitStructure.CAN_Prescaler = BRP;  //��Ƶϵ��(Fdiv)Ϊbrp+1	
	CAN_Init(CAN1, &CAN_InitStructure);
	
	/* ��ʼ��CAN������ */
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	CAN_FilterInitStructure.CAN_FilterNumber = 0;   // ������0
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;   // ����λģʽ
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;   // 32λ 
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;   // 32λID
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;   // 32λMASK
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;   // ������0������FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;   // ���������0
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	/* �ж����� */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);	// FIFP0��Ϣ�Һ��ж�����
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}

uint8_t CAN1_Send(uint8_t* Data, uint8_t Len) {
	/* ���÷��ͱ��Ľṹ�� */
	CanTxMsg TxMessage;
	TxMessage.StdId = 0x12;   // ���ñ�׼��ʶ��
	TxMessage.ExtId = 0x00;   // ������չ��ʶ��
	TxMessage.IDE = CAN_Id_Standard;   // ʹ�ñ�׼��ʽ
	TxMessage.RTR = CAN_RTR_DATA;   // ��Ϣ����Ϊ����֡��һ֡8λ��
	TxMessage.DLC = Len;
	
	/* ���֡���ݶ� */
	for(uint8_t i = 0; i < Len; i++) {
		TxMessage.Data[i] = Data[i];
	}
	
	/* ���ͱ��� */
	uint8_t mbox = CAN_Transmit(CAN1, &TxMessage);
	uint16_t timeout = 0;
	while((CAN_TransmitStatus(CAN1, mbox) == CAN_TxStatus_Failed) && (timeout < 0xFFF)) timeout++;
	
	return (timeout < 0xFFF) ? 1 : 0;
}

//uint8_t CAN1_Receive(uint8_t* Data) {
//	CanRxMsg RxMessage;
//	if (CAN_MessagePending(CAN1, CAN_FIFO0) == 0) return 0;
//	
//	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
//	for (uint8_t i = 0; i < 8; i++) {
//		Data[i] = RxMessage.Data[i];
//	}
//	return RxMessage.DLC;
//}

void USB_LP_CAN1_RX0_IRQHandler(void) {
	CanRxMsg RxMessage;
	RxMessage.StdId = 0x00;
	RxMessage.ExtId = 0x0000;
	RxMessage.IDE = 0;
	RxMessage.RTR = 0;
	RxMessage.DLC = 0;
	RxMessage.FMI = 0;
	for(uint8_t i = 0; i < 8; i++) {
		RxMessage.Data[i] = 0x00;
	}
	
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	uint8_t count = RxMessage.DLC;
	
	if (RxMessage.StdId == 0x12) {
		for(uint8_t i = 0; i < count; i++) {
			CAN1_RxPacket[i] = RxMessage.Data[i];
		}
	}
}
