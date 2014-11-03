//__________________________________________________________
// BINOME :
// ETAT : 
//__________________________________________________________

//____ registres de périphériques du stm_32
#include "stm32f10x.h"
#include "accelero.h"

int test_accelero(void); 
int capteur_adc;
int main (void)
{ 
	accelero_init();
	while (1) {
		capteur_adc = accelero_getAngle();
	}
	return 0;
}


