#include "comusart.h"

void sendChar(uint8_t ch){
	while(!(USART2->SR & USART_SR_TXE));
		USART2->DR =ch;
		while(!(USART2->SR & USART_SR_TC));
}
uint8_t ReceiveChar(void){
	while(!(USART2->SR & USART_SR_RXNE));
	return (uint8_t)USART2->DR;

}
void SendString(char* str){
	while(*str){
		SendChar(*str++);
	}

}
