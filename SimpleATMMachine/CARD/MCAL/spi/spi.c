/*
 * spi.c
 *
 * Created: 4/28/2023 1:44:45 PM
 *  Author: Speed
 */ #include "spi.h"
 void SPI_initMaster(void)
 {
 DIO_init(PORT_B,4,OUTPUT);
 DIO_init(PORT_B,5,OUTPUT);
 DIO_init(PORT_B,7,OUTPUT);
 DIO_init(PORT_B,6,INPUT);

 SET_BIT(SPCR,SPE);
 SET_BIT(SPCR,MSTR);
 
 }
 void SPI_initSlave(void)
 {
 DIO_init(PORT_B,4,INPUT);
 DIO_init(PORT_B,5,INPUT);
 DIO_init(PORT_B,7,INPUT);
 DIO_init(PORT_B,6,OUTPUT);

 SET_BIT(SPCR,SPE);

 }
 void SPI_sendByte(u8 data)
 {
 SPDR=data;
 while(GET_BIT(SPSR,SPIF)==0);
 }
 u8 SPI_receiveByte(void)
 {


 while(GET_BIT(SPSR,SPIF)==0) ;

 return SPDR;
 }
 void SPI_sendString(u8*string)
 {
 while(*string!='\0')
 {
 SPI_sendByte(*string);
 string++;

 }
 }
 void SPI_receiveString(u8*string)
 {
 u8 i=0;
 string[i]=SPI_receiveByte();
 while(string[i]!='#')
 {
 i++;
 string[i]=SPI_receiveByte();

 }
 string[i]='\0';
 }
