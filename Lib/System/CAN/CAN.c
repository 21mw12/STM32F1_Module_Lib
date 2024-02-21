#include "CAN.h"

uint8_t CAN1_RxPacket[8] = {0x00};

void CAN1_Init(void) {
	/* 初始化时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	/* 初始化引脚 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* 初始化CAN */	
	CAN_InitTypeDef CAN_InitStructure;	
	CAN_InitStructure.CAN_TTCM = DISABLE;   // 非时间触发通信模式   
	CAN_InitStructure.CAN_ABOM = DISABLE;   // 软件自动离线管理	  
	CAN_InitStructure.CAN_AWUM = DISABLE;   // 睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)
	CAN_InitStructure.CAN_NART = ENABLE;   	// 不使用报文自动传送 
	CAN_InitStructure.CAN_RFLM = DISABLE;   // 报文不锁定,新的覆盖旧的  
	CAN_InitStructure.CAN_TXFP = DISABLE;   // 优先级由报文标识符决定 
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;   //CAN工作模式设置 
	CAN_InitStructure.CAN_SJW = SWJ;   			// 重新同步跳跃宽度为tsjw+1个时间单位
	CAN_InitStructure.CAN_BS1 = BS1;
	CAN_InitStructure.CAN_BS2 = BS2;
	CAN_InitStructure.CAN_Prescaler = BRP;  //分频系数(Fdiv)为brp+1	
	CAN_Init(CAN1, &CAN_InitStructure);
	
	/* 初始化CAN过滤器 */
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	CAN_FilterInitStructure.CAN_FilterNumber = 0;   // 过滤器0
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;   // 屏蔽位模式
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;   // 32位 
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;   // 32位ID
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;   // 32位MASK
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;   // 过滤器0关联到FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;   // 激活过滤器0
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	/* 中断配置 */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);	// FIFP0消息挂号中断允许
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}

uint8_t CAN1_Send(uint8_t* Data, uint8_t Len) {
	/* 配置发送报文结构体 */
	CanTxMsg TxMessage;
	TxMessage.StdId = 0x12;   // 设置标准标识符
	TxMessage.ExtId = 0x00;   // 设置扩展标识符
	TxMessage.IDE = CAN_Id_Standard;   // 使用标准格式
	TxMessage.RTR = CAN_RTR_DATA;   // 消息类型为数据帧（一帧8位）
	TxMessage.DLC = Len;
	
	/* 填充帧数据段 */
	for(uint8_t i = 0; i < Len; i++) {
		TxMessage.Data[i] = Data[i];
	}
	
	/* 发送报文 */
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
