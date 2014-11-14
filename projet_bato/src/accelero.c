
#include "accelero.h"
#include "stm32f10x_adc.h"
#include "math.h"

GPIO_InitTypeDef GPIO_InitStructure;
ADC_InitTypeDef  ADC_InitStructure;

/* Channel mapping for PC0 (axis X) with ADC12_10 */
const uint8_t ADC_Channel_X = ADC_Channel_10;
/* Channel mapping for PC1 (axis Y) with ADC12_11 */
const uint8_t ADC_Channel_Y = ADC_Channel_11;

/* These values are deduced from experimental captures of X and Y*/
const uint16_t OFFSET_X = 19000;
const uint16_t OFFSET_Y = 37000;
const uint16_t RADIUS = 8600;
/* Valeurs expérimentaux de X et Y pour les points critiques :
	-90 degree : 19000 29000 -> 0   1
  -45 degree : 24000 35800 -> 0.7 0.7
	0 degree   : 27000 37000 -> 1   0  
	45 degree  : 32000 35800 -> 0.7 0.7
	90 degree  : 36000 29000 -> 0   1
*/

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

int launchCapture(uint8_t ADC_Channel) {
	ADC_RegularChannelConfig(ADC2, ADC_Channel, 1, ADC_SampleTime);
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);
	while (!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));
	ADC_ClearFlag(ADC2, ADC_FLAG_STRT);
	return ADC_GetConversionValue(ADC2);
}

int accelero_getValX(void) {
	return launchCapture(ADC_Channel_X);
}

int accelero_getValY(void) {
	return launchCapture(ADC_Channel_Y);
}

/* TODO : formule à refaire.. */
double x; double y;
double accelero_getAngle() {
	x = (double) (RADIUS - (accelero_getValX() - OFFSET_X));
	y = (double) (RADIUS - (accelero_getValY() - OFFSET_Y));
	return 180*atanf(tan(fabs(y)/fabs(x)));
}