/*
 * spi.c
 *
 * Created: 4/28/2023 1:44:45 PM
 *  Author: Speed
 */ 
#include "spi.h"
void SPI_initMaster(void)
{
	DIO_init(PORT_B,4,OUTPUT);
	DIO_init(PORT_B,5,OUTPUT);
	DIO_init(PORT_B,7,OUTPUT);
	DIO_init(PORT_B,6,INPUT);
	DIO_write(PORT_B,4,HIGH);
	
	
	SET_BIT(SPCR,SPE);
	SET_BIT(SPCR,MSTR);
	
	//CLR_BIT(SPSR, SPI2X);
	//SET_BIT(SPCR,SPR0);
	//SET_BIT(SPCR,SPR1);

}
void SPI_initSlave(void)
{
	 DIO_init(PORT_B,4,INPUT);
	 DIO_init(PORT_B,5,INPUT);
	 DIO_init(PORT_B,7,INPUT);
	 DIO_init(PORT_B,6,OUTPUT);

	 SET_BIT(SPCR,SPE);

}


void SPI_startTransmission (void)
{
	DIO_write(PORT_B,4,LOW);
}

u8 SPI_transmitByte(u8 data)
{
	 /*Master*/
	 
	u8 flushBuffer;
	 
	 SPDR=data;
	 
	 while(GET_BIT(SPSR,SPIF)==0);
	 
	 flushBuffer = SPDR;
	 
	 return flushBuffer;
}
void SPI_stopTransmission (void)
{
	 DIO_write(PORT_B,4,HIGH);
}


 void SPI_sendString(u8*string)
 {
	while(*string!='\0')
	{
		//SPI_sendByte(*string);
		string++;

	}
 }
 void SPI_receiveString(u8*string)
 {
	u8 i=0;
	//string[i]=SPI_receiveByte();
	while(string[i]!='#')
	{
		i++;
		//string[i]=SPI_receiveByte();

 	}
 	string[i]='\0';
 }
