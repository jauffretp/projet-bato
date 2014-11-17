
#include "accelero.h"

int capteur_adc_X;
int capteur_adc_Y;
int depasser_45Deg;
int accelero_getValX(void);
int accelero_getValY(void);

/* Valeurs expérimentaux de X et Y pour les points critiques :
	-90 degree : 19000 29000 
  -45 degree : 24000 35800
	0 degree   : 27000 37000
	45 degree  : 32000 35800
	90 degree  : 36000 29000
*/
void test_accelero() {
	accelero_init();
	while (1) {
		int i = 1000;
		while(i--);
		capteur_adc_X = accelero_getValX();
		capteur_adc_Y = accelero_getValY();
		depasser_45Deg = accelero_exceed45Deg();
	}
}