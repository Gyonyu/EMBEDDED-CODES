
#include "conf.h"
#include <stm32f446xx.h>

// --------- Function ---------
// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

int main(void){
	config();
	char auxChar;
	while(1){
		auxChar=ReceiveChar();
		SendChar(auxChar);
	}
}

