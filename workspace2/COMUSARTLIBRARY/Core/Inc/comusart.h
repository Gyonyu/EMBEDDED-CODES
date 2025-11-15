#ifndef COMUSART_H_
#define COMUSART_H_
//typedef unsigned char uint8_t;
#include <stm32f446xx.h>

void sendChar(uint8_t);/*only works for usart 2*/
uint8_t ReceiveChar(void);
void SendString(char*);

#endif
