#include <stm32f4xx.h>
#include "conf.h"

void confRCC(void){
RCC->AHB1ENR |= (1<<6);//PE
RCC->APB2ENR |= (1<<14);
}

void confGPIO(void){
	GPIOE->MODER |= (1<<2);//PE1COMOSALIDA
	GPIOE->PUPDR |= (1<<0);//PE0 COMO ENTRADA PULLUP

}

void confSYSCFG(void){
SYSCFG->EXTICR[0] |= (4<<0);//ACTIVAMOS LA INTERRUPCION DE PC13
}

void confEXTI(void){
EXTI->IMR |=(1<<0);	//ACTIVAMOS LA LINEA 13 DE LA INTERRPUCION
EXTI->FTSR |= (1<<0);//ACTIVAMOS EL FALLING DE NUESTRA INTERRUUPCION 

}

void confNVIC(void){
NVIC_EnableIRQ(EXTI0_IRQn);
NVIC_SetPriority(EXTI0_IRQn,1);
}
