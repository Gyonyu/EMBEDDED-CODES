#include <stm32f446xx.h>
#include "conf.h"
/*funciones imlementadas*/


void confRCC(void){
	RCC->AHB1ENR |= (1 << 0)|(1<<1); // A  	YB
	RCC->APB1ENR |= (1<<2);//ACTIVAMOS CLK DEL TIM4
}

void confGPIO(void){
	
	GPIOA->MODER |= ( 1<< 10); // PA5 Output 
	GPIOB->MODER |= ( 2<< 12); // PB6 INPUT
	GPIOB->PUPDR |= ( 2<< 12); //PULLDOWN EN PB6
	GPIOB->AFR[0] |=(2<<24);//CARGAMOS LA FUCNION ESPECIAL DEL TIM4
}


void setClkPLL(void)
{
	RCC->CR |=(1 << 16);
	while(!(RCC->CR & RCC_CR_HSERDY));
	/*Acivamos el prefetch del FLASH y cambiamos la latencia entre lectura de la CPU y la memoria a 2 waitstates*/
	FLASH->ACR |= (1<<8) ;
	FLASH->ACR |= (5<<0);
	/*Cambiamos la velicidad del apb1 ya que no puede trabajar a mas de 45MHZ y la de apb2 que no trabaja a mas 90*/
	RCC->CFGR |= (5<<10);
	RCC->CFGR |= (4<<13);
	RCC->PLLCFGR |=(1 << RCC_PLLCFGR_PLLSRC_Pos);
	RCC->PLLCFGR |= (360 << RCC_PLLCFGR_PLLN_Pos) | 
									(8 << RCC_PLLCFGR_PLLM_Pos) | 
									(0 << RCC_PLLCFGR_PLLP_Pos) ;
	/*LAS VELOCIDADES DEL AHB, EL APB1,APB2 DEBEN MODIFICARSE SI CAMBIO LA FRECUENCIA A LA MAS ALTA*/
	RCC->CR |=(1 << 24);
	RCC->CFGR |= (2 << 0);
	SystemCoreClockUpdate();
}

void confTIMER(void)
{
	//estos valores son para un periodo de 100ms
	TIM4->ARR = 0XFFFF;
	TIM4->PSC =1;
	TIM4->CCMR1 |=(1<<0);//HABILITAMOS EL CANAL 1 EN MODO INPUTCAPTURE Y LO RELACIONAMOS TI1
	TIM4->CCMR1 |=(3<<4);//ACTIVAMOS FILTRO PARA EL INPUTCAPTURE N=8
	//TIM4->CCER&=~((1<<1)|(1<<3));
	TIM4->CR1 |=(0X81 <<0); //activamos la autorecarga en el buffer y el contador
	//TIM4->DIER |= TIM_DIER_UIE;
	TIM4->CCER |= (1<<0);
	TIM4->SMCR |= (7<<0)|(5<<4);
	TIM4->EGR |= (1<<0);
}


void confNVIC(void){
NVIC_EnableIRQ(TIM4_IRQn);
	NVIC_SetPriority(TIM4_IRQn,1);
}

void TIM4_IRQHandler(void){
	if(TIM4->SR &TIM_SR_UIF)
		TIM4->SR &= ~(1<<0);
		GPIOA->ODR ^= GPIO_ODR_OD5;
}
