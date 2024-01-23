#include "AD.h"

#if ADCChannelCount > 0

uint16_t AD_Value[ADCChannelCount+1];

/**
  * @brief 
  * @param 
  * @return 
  */
void AD_InitPAPort(uint8_t AD_InitPAPort_Count) {
	uint16_t Enable_GPIO_Pin = 0;

	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* ѡ��Ҫ���������� */
	switch (AD_InitPAPort_Count) {
		case 7:
			Enable_GPIO_Pin |= GPIO_Pin_7;
		case 6:
			Enable_GPIO_Pin |= GPIO_Pin_6;
		case 5:
			Enable_GPIO_Pin |= GPIO_Pin_5;
		case 4:
			Enable_GPIO_Pin |= GPIO_Pin_4;
		case 3:
			Enable_GPIO_Pin |= GPIO_Pin_3;
		case 2:
			Enable_GPIO_Pin |= GPIO_Pin_2;
		case 1:
			Enable_GPIO_Pin |= GPIO_Pin_1;
		case 0:
			Enable_GPIO_Pin |= GPIO_Pin_0;
	}

	/* ����GPIO */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = Enable_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief 
  * @param 
  * @return 
  */
void AD_InitPBPort(uint8_t AD_InitPBPort_Count) {
	uint16_t Enable_GPIO_Pin = 0;

	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	/* ѡ��Ҫ���������� */
	switch (AD_InitPBPort_Count) {
		case 9:
			Enable_GPIO_Pin |= GPIO_Pin_1;
		case 8:
			Enable_GPIO_Pin |= GPIO_Pin_0;
	}

	/* ����GPIO */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = Enable_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief 
  * @param 
  * @return 
  */
void AD_InitPCPort(uint8_t AD_InitPCPort_Count) {
	uint16_t Enable_GPIO_Pin = 0;

	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* ѡ��Ҫ���������� */
	switch (AD_InitPCPort_Count) {
		case 15:
			Enable_GPIO_Pin |= GPIO_Pin_5;
		case 14:
			Enable_GPIO_Pin |= GPIO_Pin_4;
		case 13:
			Enable_GPIO_Pin |= GPIO_Pin_3;
		case 12:
			Enable_GPIO_Pin |= GPIO_Pin_2;
		case 11:
			Enable_GPIO_Pin |= GPIO_Pin_1;
		case 10:
			Enable_GPIO_Pin |= GPIO_Pin_0;
	}

	/* ����GPIO */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = Enable_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void AD_Init() {
	/* ����ʱ�Ӻͷ�Ƶ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	/* ����GPIO */
	AD_InitPAPort(ADCChannelCount);
	if (ADCChannelCount > 7)	AD_InitPBPort(ADCChannelCount);
	if (ADCChannelCount > 9) AD_InitPCPort(ADCChannelCount);
	
	/* ѡ�������Ķ�·ͨ�� */
	switch (ADCChannelCount) {
		case 15:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 16, ADC_SampleTime_55Cycles5);
		case 14:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 15, ADC_SampleTime_55Cycles5);
		case 13:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 14, ADC_SampleTime_55Cycles5);
		case 12:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 13, ADC_SampleTime_55Cycles5);
		case 11:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 12, ADC_SampleTime_55Cycles5);
		case 10:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 11, ADC_SampleTime_55Cycles5);
		case 9:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 10, ADC_SampleTime_55Cycles5);
		case 8:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 9, ADC_SampleTime_55Cycles5);
		case 7:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_55Cycles5);
		case 6:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_55Cycles5);
		case 5:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_55Cycles5);
		case 4:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5);
		case 3:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
		case 2:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
		case 1:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
		case 0:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	}
	
	/* ����ADCת���� */
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;										// ��������ģʽ
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;								// ���ݶ��뷽ʽ
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// �ⲿ����Դ
#if isContinuousConversion == 1
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;										// ����ת��
#else 
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;									// ����ת��
#endif
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;													// ɨ��ģʽ
	ADC_InitStruct.ADC_NbrOfChannel = ADCChannelCount+1;								// ת��ͨ����Ŀ
	ADC_Init(ADC1, &ADC_InitStruct);
	
	/* DMA���� */
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;							// �������ʼ��ַ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	// ��������ݿ��
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;						// ����ĵ�ַ�Ƿ�����
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;									// �洢������ʼ��ַ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;					// �洢�������ݿ��
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;											// �洢���ĵ�ַ�Ƿ�����
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;													// ���䷽��(������Ϊ����Դ)
	DMA_InitStructure.DMA_BufferSize = ADCChannelCount+1;												// ��������С(�������)
#if isContinuousConversion == 1
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;															// �Ƿ�ʹ���Զ���װ���Զ���װ�������������ͬʱʹ�ã�
#else 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
#endif
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;																// �Ƿ��Ǵ洢�����洢�����Ƿ����������
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;												// ���ȼ�
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	/* ʹ��DMA */
	DMA_Cmd(DMA1_Channel1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	
	/* ����ADC */
	ADC_Cmd(ADC1, ENABLE);
	
	/* ADCУ׼ */
	ADC_ResetCalibration(ADC1);
		while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
		while (ADC_GetCalibrationStatus(ADC1) == SET);
		
#if isContinuousConversion == 1
	/* ������� */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
#endif
}

#if isContinuousConversion == 0
void AD_GetValue(void) {
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, 5);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	// �������
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1));
	DMA_ClearFlag(DMA1_FLAG_TC1);
}
#endif

#else

void AD_Init() {
	/* ����ʱ�Ӻͷ�Ƶ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	/* ����GPIO */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
	
	/* ѡ�������Ķ�·ͨ�� */
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	
	/* ����ADCת���� */
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;										//ADC��������ģʽ
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;								//���ݶ��뷽ʽ
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//�ⲿ����Դ
#if isContinuousConversion == 1
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;										//����ת��
#else
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;									//����ת��
#endif
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;												//ɨ��ģʽ
	ADC_InitStruct.ADC_NbrOfChannel = 1;															//ת��ͨ����Ŀ
	ADC_Init(ADC1, &ADC_InitStruct);
	
	/* ����ADC */
	ADC_Cmd(ADC1, ENABLE);
	
	/* ADCУ׼ */
	ADC_ResetCalibration(ADC1);
		while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
		while (ADC_GetCalibrationStatus(ADC1) == SET);
		
#if isContinuousConversion == 1
	/* ������� */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
#endif
}

uint16_t AD_GetValue(void) {
#if isContinuousConversion == 0
	/* ������� */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	/* �ȴ�ת����� */
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
#endif
  return ADC_GetConversionValue(ADC1);
}

#endif
