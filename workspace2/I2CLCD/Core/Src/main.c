
#include "conf.h"
#include <stm32f446xx.h>
#include "lcdi2c.h"

int main(void){
	config();
	LCD_Init();
	LCD_SendString("Hola");
	delay_ms(1000);
	LCD_ReturnHome();
	LCD_SendString("Ya C I2C");
	while (1)
	{	
	}
	
}

