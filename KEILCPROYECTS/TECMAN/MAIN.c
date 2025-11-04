#include <stm32f446xx.h>
#include "tecmat4x4.h"
#include "conf.h"

const uint8_t sevenSeg[16]={
	0X40,0X79,0X24,0X30,0X19,0X12,0X02,0X78,
	0X00,0X18,0X08,0X03,0X46,0X21,0X06,0X0E
};

int main (void){
	confRCC();
	confGPIO();
	while(1){
	uint8_t keypress = gotKey();
		if(keypress != 0x88){
			if(keypress >= 0x30 && keypress <= 0x39){//VERIFICAMOS SI SE PRESIONO UN DIGITO DEL 0 AL 9
			keypress-=0x30;
			GPIOF->ODR = sevenSeg[keypress];
			}
			else{ //VERIFICAMOS SI SE PRESIONÓ A-F
				keypress-= 0x37;
				GPIOF->ODR = sevenSeg[keypress];
			}
		}
		else{
		GPIOF->ODR = (0X7F);
		}
	}
}