/*
 * esp8266.c
 *
 * Created: 5/2/2023 1:06:12 AM
 *  Author: Speed
 */ 

#include "esp8266.h"

void ESP8266_Init(void)
{
	
TIMER_init(TIMER_2);
TIMER_start(TIMER_2);
	UART_Init();
	ESP8266_Reset();
}

void ESP8266_Reset(void)
{
	// Send reset command to ESP8266
	UART_sendString("AT+RST\r\n");
	
	// Wait for reset to complete
TIMER_delay(TIMER_2,1000);
}

void ESP8266_Connect(char* ssid, char* password)
{
	// Set WiFi mode to client
	UART_sendString("AT+CWMODE=1\r\n");
TIMER_delay(TIMER_2,1000);
	
	// Connect to WiFi network
	char command[100];
	sprintf(command, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
	UART_sendString(command);
	
	// Wait for connection to complete
TIMER_delay(TIMER_2,5000);
}

void ESP8266_SendData(char* ip, int port, char* data)
{
	// Establish TCP connection to remote server
	char command[100];
	sprintf(command, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ip, port);
	UART_sendString(command);
	
	// Wait for connection to complete
TIMER_delay(TIMER_2,2000);

	
	// Send data over TCP connection
	sprintf(command, "AT+CIPSEND=%d\r\n", strlen(data));
	UART_sendString(command);
	UART_sendString(data);
	
	// Wait for data to be sent
TIMER_delay(TIMER_2,2000);
}

char* ESP8266_ReceiveData(char* ip, int port)
{
	// Establish TCP connection to remote server
	char command[100];
	sprintf(command, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ip, port);
	UART_sendString(command);
	
	// Wait for connection to complete
	TIMER_delay(TIMER_2,2000);

	// Set up for receiving data
	UART_sendString("AT+CIPMODE=1\r\n");
	UART_sendString("AT+CIPSEND\r\n");
	
	// Wait for data to be received
	TIMER_delay(TIMER_2,5000);

	// Read data from ESP8266 module
	char* data = UART_recieveString();
	
	return data;
}

void ESP8266_Close(void)
{
	// Close TCP connection
	UART_sendString("AT+CIPCLOSE\r\n");
	
	// Wait for connection to close
TIMER_delay(TIMER_2,1000);
}
