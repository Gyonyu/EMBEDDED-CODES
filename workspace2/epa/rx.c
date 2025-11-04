/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "nrf24.h"  // Asegúrate de incluir tu librería NRF24
#include <stdio.h>   // Para debugging

SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */
#define SIZE_RX_BUF 4

nrf24 nrfRx;
uint8_t rx_data[SIZE_RX_BUF];
uint8_t rx_address[] = {0xEA, 0xDD, 0xCC, 0xBB, 0xAA};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SPI2_Init();

  // Configuración de pines para NRF24
  nrfRx.CE_port = GPIOB;
  nrfRx.CE_pin = GPIO_PIN_10;
  nrfRx.CSN_port = GPIOB;
  nrfRx.CSN_pin = GPIO_PIN_12; 
  nrfRx.IRQ_port = GPIOB;
  nrfRx.IRQ_pin = GPIO_PIN_11;
  nrfRx.hSPIx = &hspi2;

  // Inicialización NRF24
  NRF24_Init(&nrfRx);
  NRF24_Set_RxAddress(&nrfRx, rx_address);
  NRF24_Set_DataRate(&nrfRx, _250KBS);
  NRF24_Set_PALevel(&nrfRx, HIGH);
  
  // Configurar como receptor
  NRF24_Set_Mode(&nrfRx, RX_MODE);

  while(1)
  {
    // Verificar si hay datos disponibles
    if(NRF24_DataReady(&nrfRx))
    {
      // Leer los datos recibidos
      NRF24_Receive(&nrfRx, rx_data, sizeof(rx_data));
      
      // Aquí puedes procesar los datos recibidos
      // rx_data[0] debería contener el valor 27
      
      // Por ejemplo, podrías encender un LED o enviar por UART
      if(rx_data[0] == 27)
      {
        // Datos recibidos correctamente
        // Agrega aquí tu lógica para manejar la recepción
      }
    }
    
    HAL_Delay(10);  // Pequeña espera para no saturar
  }
}

// Los demás funciones (SystemClock_Config, MX_SPI2_Init, MX_GPIO_Init) 
// se mantienen igual que en tu código original