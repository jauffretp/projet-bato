//____ registres de périphériques du stm_32
#include "accelero.h"
#include "girouette.h"
#include "interrupt.h"

void test_accelero(void); 

int main (void)
{ 
	//test_accelero();
	interrupt_init();
	interrupt_run();
	return 0;
}

	