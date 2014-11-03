
#include "accelero.h"
#include "stm32f10x_gpio.h"


GPIO_InitTypeDef GPIO_InitStructure;
ADC_InitTypeDef  ADC_InitStructure;


uint8_t ADC_SampleTime = ADC_SampleTime_239Cycles5;

void accelero_init(void) {
	
	/* Clock config */
	// ADCCLK = PCLK2/4 
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 |
                         RCC_APB2Periph_GPIOC, ENABLE);
	
	/* GPIO Config */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/* ADC Config */
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC2, &ADC_InitStructure);
	
	/* ADC2 regular channels configuration */ 
  ADC_RegularChannelConfig(ADC2, ADC_Channel_10, 1, ADC_SampleTime);
  //ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 2, ADC_SampleTime);
	
	/* Start ADC (AD_ON) */
	ADC_Cmd(ADC2, ENABLE);
	
}

int accelero_getAngle(void) {
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);
	while (!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));
	ADC_ClearFlag(ADC2, ADC_FLAG_STRT);
	return ADC_GetConversionValue(ADC2);
}
