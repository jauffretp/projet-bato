#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "misc.h"

void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);

void initGirouette() {
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE) ;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE) ;
TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge , TIM_ICPolarity_BothEdge);
TIM_SetAutoreload(TIM3,1440);
TIM_Cmd(TIM3, ENABLE);
	
GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);

	
NVIC_InitTypeDef configNVIC ;
configNVIC.NVIC_IRQChannel = EXTI9_5_IRQn;
configNVIC.NVIC_IRQChannelCmd = ENABLE;
configNVIC.NVIC_IRQChannelPreemptionPriority = 0x1;
configNVIC.NVIC_IRQChannelSubPriority = 0x1;
NVIC_Init(&configNVIC);	
	
EXTI_InitTypeDef configExt ;
configExt.EXTI_Line = EXTI_Line5;
configExt.EXTI_LineCmd = ENABLE;
configExt.EXTI_Mode = EXTI_Mode_Interrupt;
configExt.EXTI_Trigger = EXTI_Trigger_Rising;
EXTI_Init(&configExt);


	
while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) == 0){}
TIM_SetCounter(TIM3,0);
	
}

int getAngleGirouette() {
	if(TIM_GetCounter(TIM3)<720) {
		return (TIM_GetCounter(TIM3)*180)/720;
		}	
	else {
		return ((1439-TIM_GetCounter(TIM3))*180)/720;
		}
}

void EXTI9_5_IRQHandler(void){
	TIM_SetCounter(TIM3,0);
}
