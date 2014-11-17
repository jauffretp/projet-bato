#include "interrupt.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"

int a = 0;

void SysTick_Handler(void) {
	if (a == 0) 
		a = 1;
	else 
		a = 0;
}

void interrupt_init(void) {  
	
	if (SysTick_Config(1000000))
  { 
    /* Capture error */ 
    while (1);
  }
}

void interrupt_run(void) {
	while(1);
}
