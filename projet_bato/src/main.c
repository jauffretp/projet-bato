//____ registres de périphériques du stm_32
#include "accelero.h"

/*
 * En mode simul : changer la tension ADC2 voie 10 et 
 * capturer capteur_adc sur le Logic Analyzer pour visualiser le changement  
 */
void test_accelero(void); 
int capteur_adc;


int main (void)
{ 
	test_accelero();
	return 0;
}

void test_accelero() {
	accelero_init();
	while (1) {
		int i = 1000;
		while(i--);
		capteur_adc = accelero_getAngle();
	}
}


	