#include <stm32f446xx.h>
#include "conf.h"
/*protoripado de funciones*/
void delay_ms(uint32_t delay);
uint16_t veclit [19] = {0x3800,0x1C00,0x0E00,0x0700,0x0300,0x0100,0x0300,0x0700,0x0E00,0x1C00,0x3800,0x7000,0xE000,0xC000,0x8000,0xC000,0xE000,0x7000}; 

	int main(void){
	//setClkHSE();
	setClkPLL();
	confRCC(); 
	confGPIO();
	int delay_val = 10;
	while(1){
	for(uint8_t i = 0;i<18;i++){
	GPIOE->ODR = veclit[i]; 
	if(GPIOA->IDR  & (1 << 5) && delay_val < 100) 
	{
	delay_val = delay_val + 1;	
	}
	if(GPIOA->IDR  & (1 << 6) && delay_val >10) 
	{
	delay_val = delay_val - 1;	
	}
	delay_ms(delay_val);	
	}
}
	}	
/*functions*/
void delay_ms(uint32_t delay){
	for(uint32_t i=0;i<delay;i++){
	for(uint32_t j=0;j<11500;j++);
	}
}

