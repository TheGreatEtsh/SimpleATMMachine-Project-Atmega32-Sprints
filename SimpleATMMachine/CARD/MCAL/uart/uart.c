/*
 * uart.c
 *
 * Created: 5/1/2023 2:57:57 PM
 *  Author: Ahmed Hesham
 */ 

#include "uart.h"

void UART_Init(void)
{
	// Set BaudRate -> 9600/12MhZ
	UBRRL = 51;
	UBRRH = 0;
	// Set Frame Format -> 8 data, 1 stop, No Parity
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	SET_BIT(UCSRC,URSEL);
	
	// Enable RX and TX
	UCSRB = 0x18;
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);

}

void UART_SendChar(u8 data)
{
	// Wait until transmission Register Empty
	
	while(GET_BIT(UCSRA,UDRE) == 0x00);
	UDR = data;
}

u8 UART_GetChar(void)
{
	u8 Result;
	// Wait until Reception Complete

	while(	GET_BIT(UCSRA,RXC) == 0x00);
	Result = UDR;

	/* Clear Flag */
	SET_BIT(UCSRA,RXC);
	return Result;

}


void UART_sendString(u8 *str)
{
	u8 i=0;


	while(str[i]!='\0')
	{
		UART_sendByte(str[i]);
		i++;

	}



}
u8* UART_recieveString()
{
	u8* str2;
	u8 i=0;


	do    //???????????????
	{
		UART_recieveByte(str2[i]);
		i++;

	}while(str2[i]!=0);


	return str2;

}
