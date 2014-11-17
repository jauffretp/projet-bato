#include "interrupt.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"




void interrupt_init(void) {  
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	if (SysTick_Config(1000000))
  { 
    /* Capture error */ 
    while (1);
  }
}