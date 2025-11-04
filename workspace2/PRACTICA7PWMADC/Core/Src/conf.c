#include <stm32f446xx.h>
#include "conf.h"
/*
PINOUT
PA8 -> PWM 1/1 
PA7 -> PWM 1/1 Complementario
PA0 -> ADC 1/0

Use TIM1 to generate complementary PWM outputs (main and complement) with dead
time to emulate the class-D half-bridge outputs. Modulate the PWM with an input audio 
signal (500 Hz 14 kHz). Sample the signal (either the raw PWM or the filtered output) with 
the ADC triggered by a timer at a sampling rate chosen according to the Nyquist criterion.  

*/


void confRCC(void){
    RCC->AHB1ENR |= (1 << 0) | (1 << 4); // A  E 

    RCC->APB1ENR |= (1 << 0); // TIM2 AD
    RCC->APB2ENR |= (1 << 0)  | (1<<8); // TIM1 ADC
    
}

void confGPIO(void){
	GPIOA->MODER |= (0xA<<2*7); // PWM Channels

    GPIOA->MODER |= (3<<0);//PA0 ANALOG

    GPIOA->AFR[0]|=(1<<28);
    GPIOA->AFR[1]|=(1<<0);
}

void confTIMER(void)
{
    //------- TIM1 -------
    TIM1->PSC = 1; // F_PWM = 1 Sec,
    TIM1->CCMR1 |=(6<<4); // Enable PWM
    TIM1->CCER  |=(1<<0);//ACTIVAMOS CANAL1
    TIM1->CCER  |=(1<<2);//ACTIVAMOS CANAL1
    TIM1->ARR  =80;// 16Mhz/(200kHz) F_PWM DE 200KHZ
    TIM1->BDTR|=(4<<0); //200 ns*1/62.5 ns
    TIM1->BDTR|=(1<<15);//activamos la salida del canal complementario
    TIM1->CR1|=(1<<0);//activamos cuenta
    //------- TIM2 -------
    TIM2->PSC = 9;
    TIM2->ARR  =12;// 1.6M*(1/140K) FREC DE MUESTREO DE 140KHZ
    TIM2->CCER  |=(1<<0);//ACTIVAMOS CANAL1
    TIM2->CR1|=(1<<0);//activamos cuenta
	TIM2->DIER |= TIM_DIER_UIE; //interrupcion por desbordamiento
    
}



void confADC(void){
	/*EMPEZAMOS LA CONFIGURACIÓN DEL ADC1 CON LA CONVERSIÓN EN EL CANAL 13*/
	//ADC1->SQR3|=(13<<0);
	ADC1->CR2|=(3<<0);//ACTIVAMOS CONTINUOS CONV Y ADCON
    ADC1->CR2|=(1<<30);//INICIAMOS LA CONVERSIÓN
	ADC1->CR1|=(1<<8);//SACANMODE
	ADC1->SMPR2|=(2<<0); //ESTAMOS CONFIGURANDO 28 CICLOS DE MUESTREO
    
}

void confNVIC(void){
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn, 1);

}

void config(void){
    confRCC();
    confADC();
    confGPIO();
    confTIMER();
    confNVIC();
}

