#include "stm32f10x_tim.h"
#include "stm32f10x.h"

int configure_PWM(void);//en mode capture avec la fréquence de la télécommande
//pour recevoir le signal, le capturer, connaitre le temps à 1 et
//envoyer par la télécommande et  le transferer directement au moteur

int border_voile(uint16_t CCR_Val);

int lacher_voile(void);

float convert_signal(float temps_a_1);

