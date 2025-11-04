/*Generamos dos tareas administradas por dos queue una de ellas parpadeara a una frec de 100ms y la otra tarea por cada pulsacion hara 
que esta frecuencia aumente*/
#include <stm32f446xx.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

/*Parámetros*/
#define initialms 100U
#define finalms 1000U
// --------- Function ---------
void confRCC(void);
void confGPIO(void);
/*FREE RTOS FUNCTION*/
void vTaskLed (void *);
void vTaskButton(void *);

/*ESTO ES COMO UN DICCIONARIO*/
//typedef enum {
//CMD_BLINKK = 0,
//CMD_ON = 1,
//CMD_OFF = 2
//}ledCMD_t;

QueueHandle_t xPeriodQueue = NULL;

/**/
// ---------- Class ----------
 
// -------- Variables --------
// ----------- Main -----------

int main(void){
	confRCC(); 
	confGPIO();
	
	xPeriodQueue = xQueueCreate(1,sizeof(uint32_t));
	xTaskCreate(vTaskLed,"LED TASK",100,NULL,1,NULL);
	xTaskCreate(vTaskButton,"LED TASK2",100,NULL,2,NULL);
	vTaskStartScheduler();
	while(1);/*JAMAS LLEGA AL WHILE DEL MAIN*/
}

void confRCC(void){
	RCC->AHB1ENR |= (1 << 0) | (1 << 4); // A  E 	
}



void confGPIO(void){
	
	GPIOA->MODER |= (5 << 10); // PA5 Y PA6 Output 
	GPIOE->PUPDR |= (1 << 16);//PEPARABOTON
}
// 3 bits en 8 
// Input en PUERTO E
void vTaskLed (void *pvPARAMETERS){
	uint32_t initdel = initialms;
	uint32_t recievedQueue;
	while(1){ 
	GPIOA->ODR ^= (1 << 5);
		TickType_t waitsTicks = (pdMS_TO_TICKS (initdel));
		if(xQueueReceive(xPeriodQueue,&recievedQueue,waitsTicks) == pdPASS)/*Recibimos el estado de la tarea2 del botoón cuando se presiono el botón si llega al tope */
		{
			if(recievedQueue < 1){
			recievedQueue = initialms;
			}
			if(recievedQueue >= finalms){
			recievedQueue=finalms;
			}
			initdel=recievedQueue;
		}
		/*esto es un delay de 0.5 s*/
	}
}
	

void vTaskButton(void *pvPARAMETERS){
	uint8_t lastState = 1;/*comprueba el ultimo estado del botón*/
	uint32_t period = initialms;
	while(1){
		uint8_t actualState;
		if(!((GPIOE->IDR) & (1 << 8)))
			actualState = 1;
			else 
				actualState = 0;
			if(lastState ==1 && actualState == 0)
			{
				vTaskDelay(pdMS_TO_TICKS(20));
				period += initialms;
				/*xQueueSend(xPeriodQueue,&period,pdMS_TO_TICKS(10))*/
				if(xQueueSend(xPeriodQueue,&period,pdMS_TO_TICKS(10)) != pdPASS){
					uint32_t temp;
				if(xQueueReceive(xPeriodQueue,&temp,0) == pdPASS)
					(void) xQueueSend(xPeriodQueue,&period,pdMS_TO_TICKS(10));
			}
			}
			lastState= actualState;
	vTaskDelay(pdMS_TO_TICKS(50));
	}
}
 