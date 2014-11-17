
#include "interrupt.h"
#include "stm32f10x_gpio.h"


int a = 0;
/* //Uncomment to debug
void SysTick_Handler(void) {
	if (a == 0) {
		GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
		a = 1;
	} else {
		a = 0;
		GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
	}
}
*/

GPIO_InitTypeDef GPIO_InitStructure;

void test_interrupt(void) {
	interrupt_init();
		/* GPIO Config */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	while(1);
	
}