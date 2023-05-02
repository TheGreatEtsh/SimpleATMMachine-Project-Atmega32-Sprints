/*
 * esp8266.h
 *
 * Created: 5/2/2023 1:06:45 AM
 *  Author: Speed
 */ 


#ifndef ESP8266_H_
#define ESP8266_H_
#include "../../MCAL/uart/uart.h"
#include "../../MCAL/timer/timer.h"
#define ESP8266_UART_BAUDRATE 9600
#define NULL ((char *)0)

void esp8266_init(void);
void ESP8266_Reset(void);
void ESP8266_Connect(char* ssid, char* password);

void ESP8266_SendData(char* ip, int port, char* data);

char* ESP8266_ReceiveData(char* ip, int port);
void ESP8266_Close(void);

#endif /* ESP8266_H_ */