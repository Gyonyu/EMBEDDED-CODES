/*
------- Kevin Lara  -------
--------- Auf Das  ---------
----------- Car  -----------
-------- 10/10/2025 --------
*/
// ------- Main Library -------
#include "conf.h"

// --------- Function ---------
void delay_ms(uint32_t delay);
// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

int main(void){
	uint32_t opt;
	config();
	CAR_Speed(65);
	while(1){
		
		switch(opt)
		{
		case '0':
			CAR_Front();
			break;
		case '1':
			CAR_Back();
			break;
		case '2':
			CAR_LeftFront();
			break;
		case '3':
			CAR_LeftBack();
			break;
		case '4':
			CAR_RightFront();
			break;
		case '5':
			CAR_RightBack();
			break;
		default:
			CAR_Speed(0);
			break;
		}
	
    }
}
	 
	

