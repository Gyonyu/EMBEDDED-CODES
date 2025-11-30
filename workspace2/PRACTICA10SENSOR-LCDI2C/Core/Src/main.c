/*
	👨🏿‍🦳👨🏿‍🦳
------- Kevin Lara  -------
--------- Auf Das  ---------
----------- I2C  -----------
-------- 02/11/2025 --------

You will read the temperature using an LM35 via ADC and display it on an LCD (using your 
previously implemented library). Two buttons (via external interrupts) will trigger scrolling: 
pressing one scrolls the display right 6 times, pressing the other scrolls left 6 times. After 
the scroll, the LCD returns home. The temperature should be updated on the screen every 
250 ms in the format: Temperature: XX.X °C. 
*/
// ------- Main Library -------
#include "conf.h"
#include <stm32f446xx.h>
#include "lcdi2c.h"

// --------- Function ---------
// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

int main(void){
	config();
	LCD_Init();
//	LCD_SendString("Tmp: ");
	delay_ms(1000);
	uint8_t x=0;
	uint8_t y=0;
	while (1)
	{	
	uint16_t adc_value = ADC1->DR; 
	float voltage = (adc_value / 4095.0) * 3.3; 
	// 4095/(3.3*10^3)*100 
	float temperature = voltage * 100.0; //  Convertir a temperatura en °C (LM35: 10mV/°C)
	LCD_SendString("Tmp: ");
	LCD_SendChar((int)temperature / 10 + '0'); // Decenas
	LCD_SendChar((int)temperature % 10 + '0'); // Unidades
	LCD_SendChar('.');
	LCD_SendChar((int)(temperature * 10) % 10 + '0');
	LCD_SendString(" C  ");
	delay_ms(250);
	LCD_SetCursor(0,0); // Vuelve al inicio para actualizar
	}
	
}


void EXTI1_IRQHandler(void){
	if(EXTI->PR & (1<<1)){
	//<<
	LCD_ScrollLeft(6);
	EXTI->PR = EXTI_PR_PR1;// EL PR ME DICE SI HUBO UNA INTERRUPCION Y LO REINICIO
// q hace despues de q se chiftie o q
}

}

void EXTI2_IRQHandler(void){
	if(EXTI->PR & (1<<2)){
	//>>
	LCD_ScrollRight(6);
	EXTI->PR = EXTI_PR_PR2;// EL PR ME DICE SI HUBO UNA INTERRUPCION Y LO REINICIO
	}

}

