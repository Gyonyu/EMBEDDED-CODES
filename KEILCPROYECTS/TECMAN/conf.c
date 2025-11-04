#include <stm32f446xx.h>
#include "conf.h"
//implementacion de funciones

extern void confRCC(void){
RCC->AHB1ENR |= (1<<3)|(1<<7);	
	
}
extern void confGPIO(void){
//condiguramos del D0-D3 DEL PD COMO SALIDAS Y 7-4 COMO ENTRADAS
	GPIOD->MODER |= (0X55 << 0);
	//
	GPIOD->OSPEEDR |= (0XFF<<0);
	//
	GPIOD->PUPDR |= (0X55<<8);
	//HAY QUE CONFIGURAR SALIDAS PARA 7SEGMENTOS
	
	GPIOF->MODER |= (0X5555 << 0);
}
	