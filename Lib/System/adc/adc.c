#include "adc.h"

void ADC_INit() {
	/*开启时钟和分频器*/
	RCC_APB2PeriphClockCmd(ADC_Periph, ENABLE);
	RCC_APB2PeriphClockCmd(ADC_IO_Periph, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	/*配置GPIO*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
	
	/*选择规则组的多路通道*/
	ADC_RegularChannelConfig(ADC, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);//设置ADC1的0通道放入规则组表单的1号位，采样时间为55.5个ADCCLK周期
	
	/*配置ADC转换器*/
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//ADC独立工作模式
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//不使用外部触发源
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//单次转换
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//非扫描模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;//转换通道数目，1个通道
	ADC_Init(ADC, &ADC_InitStruct);
	
	/*开启ADC*/
	ADC_Cmd(ADC, ENABLE);
	/*ADC校准*/
	ADC_ResetCalibration(ADC);//复位校准
	while (ADC_GetResetCalibrationStatus(ADC) == SET);//等待复位校准完成
	ADC_StartCalibration(ADC);//开始校准
	while (ADC_GetCalibrationStatus(ADC) == SET);//等待校准完成
}

uint16_t ADC_GetValue(void) {
	//软件触发
  ADC_SoftwareStartConvCmd(ADC, ENABLE);
	//等待转换完成
  while (ADC_GetFlagStatus(ADC, ADC_FLAG_EOC) == RESET);
  return ADC_GetConversionValue(ADC);
}
