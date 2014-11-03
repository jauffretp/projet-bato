
#include "accelero.h"

int test_accelero(void) { int a;
	accelero_init();
	while (1) {
		a = accelero_getAngle();
	}
	return a;
}