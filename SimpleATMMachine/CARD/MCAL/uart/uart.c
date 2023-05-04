/*
 * uart.c
 *
 * Created: 5/1/2023 2:57:57 PM
 *  Author: Ahmed Hesham
 */ 

#include "uart.h"

void UART_Init(void)
{
	
	DIO_write(PORT_D, 0, INPUT);
	DIO_write(PORT_D, 1, OUTPUT);
	// Set BaudRate -> 9600/12MhZ
	
	
	
	
	u8 UCSRCValue = 0;
	SET_BIT(UCSRCValue,7);
	CLR_BIT(UCSRB,2);
	SET_BIT(UCSRCValue,1);
	SET_BIT(UCSRCValue,2);
	CLR_BIT(UCSRCValue,4);
	CLR_BIT(UCSRCValue,5);
	CLR_BIT(UCSRCValue,3);    // to select stop bit as -> 1
	
	UBRRL = 103;
	
	UCSRC = UCSRCValue;
	
	// Set Frame Format -> 8 data, 1 stop, No Parity
	//SET_BIT(UCSRC,UCSZ0);
	//SET_BIT(UCSRC,UCSZ1);
	//SET_BIT(UCSRC,URSEL);
	
	// Enable RX and TX
	//UCSRB = 0x18;
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);

}

void UART_SendChar(u8 data)
{
	// Wait until transmission Register Empty
	UDR = data;
	while(GET_BIT(UCSRA,6) == 0x00);
	
}

u8 UART_GetChar(void)
{
	u8 Result;
	// Wait until Reception Complete

	while(	GET_BIT(UCSRA,7) == 0x00);
	Result = UDR;

	/* Clear Flag */
	//SET_BIT(UCSRA,RXC);
	return Result;

}


void UART_sendString(u8 *str)
{
	u8 i=0;


	while(str[i]!='\0')
	{
		UART_SendChar(str[i]);
		TIMER_delay(TIMER_2, 10);
		i++;

	}



}
void UART_recieveString(u8 *str)
{
	//static u8* str2;
	u8 i=0;


	do    //???????????????
	{
		str[i] = UART_GetChar();
		i++;

	}while(str[i]!='z');
	
	str[i+1] = '\0';

	//return str2;

}
