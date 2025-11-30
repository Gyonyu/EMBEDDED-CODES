#include "conf.h"
/* PINOUT
PB8 SCL
PB9 SDA
PA0 ADC1 IN0
PA1 >>
PA2 <<
*/
void confRCC(void){

    RCC->AHB1ENR |=(1<<1)|(1<<0); // GPIOB y GPIOA
    RCC->APB1ENR |=(RCC_APB1ENR_I2C1EN);//ENCENDEMOS I2C1
	RCC->APB2ENR |=(RCC_APB2ENR_SYSCFGEN);//ENCENDMOS SYSCFG PARA EXTI
	RCC->APB2ENR |=(RCC_APB2ENR_ADC1EN);//ENCENDMOS ADC1

}
void confGPIO(void){
	GPIOB->MODER |=(2<<(2*8))|(2<<(2*9));// ALTERNATE FUNCTION PB8(SCL) Y PB9(SDA)
	GPIOB->AFR[1] |=(4<<(4*0))|(4<<(4*1));//AF4 EN PB8 (bit 0-3) Y PB9 (bit 4-7)
	
	GPIOB->OTYPER|=(1<<8)|(1<<9);//opendrain PB8 Y PB9
	
	// PU PA1    || PU PA2
	GPIOA->PUPDR |=(1<<(2*1))|(1<<(2*2));
	// ADC
	GPIOA->MODER|= (3<<(2*0));//ANALOG MODE PA0
	
}


void confI2C(void){//esta configurado a traa de 8 bits con 1 bit de parada sin paridad
	I2C1->CR1 &= ~(1<<0); // Disable I2C first
	I2C1->CR2 |=(16<<0);//16mhz de frecuencia del 12c
	I2C1->CCR|=(80<<0);//estamos configurando una frecuencia de scl de fast mode
	I2C1->TRISE|=(17<<0);//TRISETIME (1000ns/62.5ns)+1=17
	I2C1->CR1 |=(1<<0); // Enable I2C
	I2C1->CR1|=I2C_CR1_ACK; // Enable ACK for slave communication
}



void confEXTI(void){
				// PA1  || PA2
	EXTI->IMR   |=(1<<1)|(1<<2); //ACTIVAMOS LA LINEA 1 DE LA INTERRPUCION
	EXTI->FTSR |= (1<<1)|(1<<2); //ACTIVAMOS EL FALLING DE NUESTRA INTERRUUPCION 

}

void confNVIC(void){
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_SetPriority(EXTI1_IRQn,1);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_SetPriority(EXTI2_IRQn,1);
}

void confADC(void){
	/*EMPEZAMOS LA CONFIGURACIÓN DEL ADC1 CON LA CONVERSIÓN EN EL CANAL 13*/
	//ADC1->SQR3|=(13<<0);
	ADC1->CR2|=(3<<0);//ACTIVAMOS CONTINUOS CONV Y ADCON
    ADC1->CR2|=(1<<30);//INICIAMOS LA CONVERSIÓN
	ADC1->CR1|=(1<<8);//SCANMODE
	ADC1->SMPR2|=(2<<0); //ESTAMOS CONFIGURANDO 28 CICLOS DE MUESTREO
    
}

void config(void){
    confRCC();
    confGPIO();
    confI2C();
	confEXTI();
	confNVIC();
	confADC();
}
