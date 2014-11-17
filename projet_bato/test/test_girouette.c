
#include "girouette.h"

int angleGirouette ;
void test_girouette(void){

	initGirouette();
	while(1){
		angleGirouette = getAngleGirouette();
	}
	
}