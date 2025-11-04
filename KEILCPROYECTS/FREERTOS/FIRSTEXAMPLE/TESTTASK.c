#include <stm32f446xx.h>
#include <FreeRTOS.h>
#include <task.h>
// --------- Function ---------
void confRCC(void);
void confGPIO(void);
/*FREE RTOS FUNCTION*/
void vTaskLed (void *);
void vTaskButton(void *);
// ---------- Class ----------
 
// -------- Variables --------
// ----------- Main -----------

int main(void){
	confRCC(); 
	confGPIO();
	xTaskCreate(vTaskLed,"LED TASK",100,NULL,1,NULL);
	xTaskCreate(vTaskButton,"LED TASK2",100,NULL,0,NULL);
	vTaskStartScheduler();
	while(1);/*JAMAS LLEGA AL WHILE DEL MAIN*/
}

void confRCC(void){
	RCC->AHB1ENR |= (1 << 0) | (1 << 4); // A  E 	
}



void confGPIO(void){
	
	GPIOA->MODER |= (5 << 10); // PA5 Y PA6 Output 
	GPIOE->PUPDR |= (1 << 16);
}
// 3 bits en 8 
// Input PA5 PA6
void vTaskLed (void *pvPARAMETERS){
	while(1){
	GPIOA->ODR ^= (1 << 5);
		vTaskDelay(500/portTICK_PERIOD_MS);
		/*esto es un delay de 0.5 s*/
	}
}
	

void vTaskButton(void *pvPARAMETERS){
	while(1){
		if(!((GPIOE->IDR) & (1 << 8))){
			GPIOA->ODR ^= (1<<6);
			vTaskDelay(100/portTICK_PERIOD_MS);
	}
}
}
