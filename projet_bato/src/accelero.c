
#include "accelero.h"
#include "stm32f10x_gpio.h"


GPIO_InitTypeDef GPIO_InitStructure;
ADC_InitTypeDef  ADC_InitStructure;

void accelero_init(void) {
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  // which mode : GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
}

int accelero_getAngle(void) {
	
	return 0;
}
