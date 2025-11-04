/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "nrf24.h"  // Asegúrate de incluir tu librería NRF24

SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */
#define SIZE_TX_BUF 4

nrf24 nrfTx;
uint8_t status_tx;
uint8_t tx_data[SIZE_TX_BUF];
uint8_t tx_address[] = {0xEA, 0xDD, 0xCC, 0xBB, 0xAA};
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
  nrfTx.CE_port = GPIOB;
  nrfTx.CE_pin = GPIO_PIN_10;
  nrfTx.CSN_port = GPIOB;
  nrfTx.CSN_pin = GPIO_PIN_12; 
  nrfTx.IRQ_port = GPIOB;
  nrfTx.IRQ_pin = GPIO_PIN_11;
  nrfTx.hSPIx = &hspi2;

  // Inicialización NRF24
  NRF24_Init(&nrfTx);
  NRF24_Set_TxAddress(&nrfTx, tx_address);
  NRF24_Set_DataRate(&nrfTx, _250KBS);
  NRF24_Set_PALevel(&nrfTx, HIGH);
  
  // Limpiar buffer de transmisión
  for(int i = 0; i < SIZE_TX_BUF; i++) {
    tx_data[i] = 0;
  }

  while(1)
  {
    tx_data[0] = 27;  // Enviar el valor 27
    
    NRF24_Set_Mode(&nrfTx, TX_MODE);
    status_tx = NRF24_Transmit(&nrfTx, tx_data, sizeof(tx_data));

    if(status_tx == 1)
    {
      // Transmisión exitosa
      NRF24_Set_Mode(&nrfTx, STANDBY);
    }
    else
    {
      // Error en la transmisión
      // Podrías agregar un manejo de error aquí
    }
    
    HAL_Delay(1000);  // Esperar 1 segundo entre transmisiones
  }
}

// Los demás funciones (SystemClock_Config, MX_SPI2_Init, MX_GPIO_Init) 
// se mantienen igual que en tu código original