#include "stm32f10x_tim.h"
#include "stm32f10x.h"

int configure_PWM(void);//en mode capture avec la fr�quence de la t�l�commande
//pour recevoir le signal, le capturer, connaitre le temps � 1 et
//envoyer par la t�l�commande et  le transferer directement au moteur

int border_voile(uint16_t CCR_Val);

int lacher_voile(void);

float convert_signal(float temps_a_1);

