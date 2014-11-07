#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


void initGirouette() {
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE) ;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE) ;
TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge , TIM_ICPolarity_BothEdge);
TIM_SetAutoreload(TIM3,1440);
TIM_Cmd(TIM3, ENABLE);
	
while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) == 0){}
TIM_SetCounter(TIM3,0);
	
}

uint16_t getAngleGirouette() {
initGirouette(); 
return TIM_GetCounter(TIM3);
}


int main (void)
{
	getAngleGirouette() ;
	while(1) ;
}
