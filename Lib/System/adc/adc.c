#include "adc.h"

void ADC_INit() {
	/*����ʱ�Ӻͷ�Ƶ��*/
	RCC_APB2PeriphClockCmd(ADC_Periph, ENABLE);
	RCC_APB2PeriphClockCmd(ADC_IO_Periph, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	/*����GPIO*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
	
	/*ѡ�������Ķ�·ͨ��*/
	ADC_RegularChannelConfig(ADC, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);//����ADC1��0ͨ��������������1��λ������ʱ��Ϊ55.5��ADCCLK����
	
	/*����ADCת����*/
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//ADC��������ģʽ
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//��ʹ���ⲿ����Դ
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//����ת��
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ
	ADC_InitStruct.ADC_NbrOfChannel = 1;//ת��ͨ����Ŀ��1��ͨ��
	ADC_Init(ADC, &ADC_InitStruct);
	
	/*����ADC*/
	ADC_Cmd(ADC, ENABLE);
	/*ADCУ׼*/
	ADC_ResetCalibration(ADC);//��λУ׼
	while (ADC_GetResetCalibrationStatus(ADC) == SET);//�ȴ���λУ׼���
	ADC_StartCalibration(ADC);//��ʼУ׼
	while (ADC_GetCalibrationStatus(ADC) == SET);//�ȴ�У׼���
}

uint16_t ADC_GetValue(void) {
	//�������
  ADC_SoftwareStartConvCmd(ADC, ENABLE);
	//�ȴ�ת�����
  while (ADC_GetFlagStatus(ADC, ADC_FLAG_EOC) == RESET);
  return ADC_GetConversionValue(ADC);
}
