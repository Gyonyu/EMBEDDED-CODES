#include <stm32f446xx.h>
#include "conf.h"

/*funciones imlementadas*/


void confRCC(void){
	RCC->AHB1ENR |= (1 << 0) | (1 << 4); // A  E 	
}

void confGPIO(void){
	
	GPIOE->MODER |= (0x5555 << 16); // PE8 -> PE15 Output 
	GPIOA->PUPDR |= (0xA << 10); //PA5 y PA6 como entrada PA5  + PA6 -
}

void setClkHSE(void){
	
	RCC->CR |=(1 << 16);
	while(!(RCC->CR & RCC_CR_HSERDY));
	/*LAS VELOCIDADES DEL AHB, EL APB1,APB2 DEBEN MODIFICARSE SI CAMBIO LA FRECUENCIA A LA MAS ALTA*/
	RCC->CFGR |= (1 << 0);
	SystemCoreClockUpdate();
}

void setClkPLL(void)
{
	RCC->CR |=(1 << 16);
	RCC->CR |=(1 << 24);
	while(!(RCC->CR & RCC_CR_HSERDY));
	/*Acivamos el prefetch del FLASH y cambiamos la latencia entre lectura de la CPU y la memoria a 2 waitstates*/
	FLASH->ACR |= (1<<8) ;
	FLASH->ACR |= (2<<0);
	/*Cambiamos la velicidad del apb1 ya que no puede trabajar a mas de 45MHZ*/
	RCC->CFGR |= (4<<10);
	RCC->PLLCFGR = (360 << RCC_PLLCFGR_PLLN_Pos) | 
									(8 << RCC_PLLCFGR_PLLM_Pos) | 
									(1 << RCC_PLLCFGR_PLLP_Pos) |
									(1 << RCC_PLLCFGR_PLLSRC_Pos);
	/*LAS VELOCIDADES DEL AHB, EL APB1,APB2 DEBEN MODIFICARSE SI CAMBIO LA FRECUENCIA A LA MAS ALTA*/
	RCC->CFGR |= (2 << 0);
	SystemCoreClockUpdate();
}
