/*
 * CARD.c
 *
 * Created: 5/1/2023 2:39:48 PM
 * Author : Ahmed Hesham
 */ 
#include "APP/app.h"
#include "MCAL/spi/spi.h"
int main ()
{
/*
	// Initialize ESP8266 module
	ESP8266_Init();
	
	// Connect to WiFi network
	ESP8266_Connect("ssid", "password");
	
	// Send data to remote server
	ESP8266_SendData("192.168.1.100", 80, "Hello, world!");
	
	// Receive data from remote server
	char* data = ESP8266_ReceiveData("192.168.1.100", 80);
	
	
	// Close TCP connection
	ESP8266_Close();
	
*/
SPI_initMaster();
SPI_sendByte("m");
SPI_sendString("momen");
	while(1)
	{
		// Do nothing
	}
}