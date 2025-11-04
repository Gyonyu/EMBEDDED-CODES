#include <stm32f446xx.h>
#include "conf.h"

int main(void){
confRCC();
confGPIO();
confSYSCFG();
confEXTI();
confNVIC();
while(1);

}

void EXTI0_IRQHandler(void){
	if(EXTI->PR & (1<<13)){
	GPIOE->ODR ^= (1<<1);
	EXTI->PR = EXTI_PR_PR13;// EL PR ME DICE SI HUBO UNA INTERRUPCION Y LO REINICIO
	}

}