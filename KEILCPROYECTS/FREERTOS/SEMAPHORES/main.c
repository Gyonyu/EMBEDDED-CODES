/*Generamos dos tareas administradas por dos queue una de ellas parpadeara a una frec de 100ms y la otra tarea por cada pulsacion hara 
que esta frecuencia aumente*/
#include <stm32f446xx.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

/*Parámetros*/
#define initialms 100U
#define finalms 1000U
// --------- Function ---------
void confRCC(void);
void confGPIO(void);
/*FREE RTOS FUNCTION*/
void vTaskA (void *);
void vTaskB (void *);
void vTaskLed (void *);
void vTaskButton(void *);


//ADMINISTRADORES DE COLA Y DE SEMAFOROS
QueueHandle_t xPeriodQueue = NULL;
SemaphoreHandle_t semaphoreA = NULL;
SemaphoreHandle_t semaphoreB = NULL;

int main(void){
	confRCC(); 
	confGPIO();
	
	xPeriodQueue = xQueueCreate(1,sizeof(uint32_t));
	semaphoreA = xSemaphoreCreateBinary();
	semaphoreB = xSemaphoreCreateBinary();
	xSemaphoreGive(semaphoreB);
	
	xTaskCreate(vTaskLed,"LED TASK",100,NULL,1,NULL);
	//xTaskCreate(vTaskButton,"BUT TASK2",100,NULL,2,NULL);
	xTaskCreate(vTaskA,"LEDA TASK",100,NULL,1,NULL);
	xTaskCreate(vTaskB,"LEDB TASK",100,NULL,1,NULL);
	vTaskStartScheduler();
	while(1);/*JAMAS LLEGA AL WHILE DEL MAIN*/
}

void confRCC(void){
	RCC->AHB1ENR |= (1 << 0) | (1 << 4); // A  E 	
}



void confGPIO(void){
	
	GPIOA->MODER |= (21 << 10); // PA5, PA6 y PA7Output 
	GPIOE->PUPDR |= (1 << 16);//PEPARABOTON
}
// 3 bits en 8 
// Input en PUERTO E
void vTaskLed (void *pvPARAMETERS){
	(void) pvPARAMETERS;
	uint32_t initdel = initialms;
	uint32_t recievedQueue;
	while(1){ 
	GPIOA->ODR ^= (1 << 7);
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
	


void vTaskA (void *pvPARAMETERS){
	(void) pvPARAMETERS;
	uint32_t period = initialms;
	while(1){
	xSemaphoreTake(semaphoreA,portMAX_DELAY);
		for(uint8_t i= 0; i<10;i++){
			GPIOA->ODR ^= (1 << 5);
			vTaskDelay(pdMS_TO_TICKS(250));
		}
		period += initialms;
		if(xQueueSend(xPeriodQueue,&period,portMAX_DELAY) != pdPASS){
					uint32_t temp;
				if(xQueueReceive(xPeriodQueue,&temp,0) == pdPASS)
					(void) xQueueSend(xPeriodQueue,&period,portMAX_DELAY);
			}
		xSemaphoreGive(semaphoreB);
	}
}
void vTaskB (void *pvPARAMETERS){
	(void) pvPARAMETERS;
	while(1){
	xSemaphoreTake(semaphoreB,portMAX_DELAY);
		for(uint8_t i= 0; i<20;i++){
			GPIOA->ODR ^= (1 << 6);
			vTaskDelay(pdMS_TO_TICKS(250));
		}
		xSemaphoreGive(semaphoreA);
	}
	}

 