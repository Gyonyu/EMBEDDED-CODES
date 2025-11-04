#include <stm32f446xx.h>
#include "conf.h"

int main(void){
confRCC();
	confGPIO();
	confTIMER();
	confNVIC();
	while(1){
	}
}