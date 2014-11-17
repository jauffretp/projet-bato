#include "gestion_bato.h"
#include "accelero.h"
#include "girouette.h"
#include "interrupt.h"
#include "stm32f10x_gpio.h"

int angle_voile;
int angle_girouette;
int angle_accelero;
int a;
void SysTick_Handler(void) {
		if (a == 0) {
		GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
		a = 1;
	} else {
		a = 0;
		GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
	}
	angle_accelero = accelero_exceed45Deg();
	if (angle_accelero) {
		angle_voile = 90;
		// border_voile(angle_voile); 
		return;
	}
	angle_girouette = getAngleGirouette();
	if (angle_girouette > 45) {
		angle_voile = 2*angle_girouette/3 - 30;
	} else {
		angle_voile = 0;
	}
	// border_voile(angle_voile); return;
}

GPIO_InitTypeDef GPIO_InitStructure;

void bato_init(void) {
	accelero_init();
	initGirouette();
	interrupt_init();
			/* GPIO Config */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// border_voile_init();
}

void bato_gestionVoile(void) {
	while(1);
}