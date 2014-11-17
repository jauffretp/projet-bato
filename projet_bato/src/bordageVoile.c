#include "bordageVoile.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"

//TIM_OCInitTypeDef configurationPWM;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t CCR1_Val = 333;
uint16_t CCR2_Val = 249;
uint16_t CCR3_Val = 166;
uint16_t CCR4_Val = 83;
uint16_t PrescalerValue = 0;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
int ARR_G;
int configure_PWM(void)
{

    
    //TIMER 4 CHANNEL 3
  /* System Clocks Configuration */
  RCC_Configuration();

  /* GPIO Configuration */
  GPIO_Configuration();

  /* -----------------------------------------------------------------------
    TIM4 Configuration: generate 4 PWM signals with 4 different duty cycles:
    The TIM4CLK frequency is set to SystemCoreClock (Hz), to get TIM4 counter
    clock at 24 MHz the Prescaler is computed as following:
     - Prescaler = (TIM4CLK / TIM4 counter clock) - 1
    SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
    and Connectivity line devices and to 24 MHz for Low-Density Value line and
    Medium-Density Value line devices

    The TIM4 is running at 36 KHz: TIM4 Frequency = TIM4 counter clock/(ARR + 1)
                                                  = 24 MHz / 666 = 36 KHz
    TIM4 Channel1 duty cycle = (TIM4_CCR1/ TIM4_ARR)* 100 = 50%
    TIM4 Channel2 duty cycle = (TIM4_CCR2/ TIM4_ARR)* 100 = 37.5%
    TIM4 Channel3 duty cycle = (TIM4_CCR3/ TIM4_ARR)* 100 = 25%
    TIM4 Channel4 duty cycle = (TIM4_CCR4/ TIM4_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */
  
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  /* Compute the prescaler value */
  int SystemCoreClock = 72000000;
  PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;
  /* Time base configuration */
  
  int horloge_sur_duree = SystemCoreClock*20000*1e-6;
  
  int TIM_PSC = (horloge_sur_duree)/65536 + 1;
  int ARR =  (horloge_sur_duree)/TIM_PSC +1;
  //ARR configuré à 20 ms
  TIM_TimeBaseStructure.TIM_Period = ARR-1;//ARR
  ARR_G = ARR-1;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PSC-1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;


  TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM4,ENABLE);
  
  TIM_Cmd(TIM4, ENABLE);
  
}


void RCC_Configuration(void)
{
  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
}



void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

#ifdef STM32F10X_CL
  /*GPIOB Configuration: TIM4 channel1, 2, 3 and 4 */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_PinRemapConfig(GPIO_FullRemap_TIM4, ENABLE);	

#else
  /* GPIOA Configuration:TIM4 Channel1, 2, 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
}


int border_voile(uint16_t CCR_Val)
{


    //faire un test avec une durée à 1 du signal de 1.5ms
    TIM_OCInitStructure.TIM_Pulse = (ARR_G*1.5)/20;

    
    //supposons que l'on trouve un angle de 45 degré
    //alors 0.1 ms -> 10 degrés
    float Ref = 1.5;
	float degre_Ref = 45;
    
    

    //mettre une autre valuer pour être à 1.6 ms
    //mesurer l'angle qui a été modifié
    //conclure sur la valeur à changer dans le CCR pour bouger de cet angle la
    //et faire la mise à l'echelle pour n'importe quel angle en fonction de cette valeur trouvée
    
   // TIM_OCInitStructure.TIM_Pulse = (45*CCR_Val)/1.5;   
    TIM_OCInitStructure.TIM_Pulse = (ARR_G*1.5)/20;
    
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	return 1;
	
}