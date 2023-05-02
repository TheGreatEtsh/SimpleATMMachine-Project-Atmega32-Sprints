/*
 * app.c
 *
 * Created: 5/1/2023 3:00:37 PM
 *  Author: Ahmed Hesham
 */ 
#include "app.h"

 void app_init (void)
 {
	 UART_Init();
	 I2C_init();
	 TIMER_init(TIMER_2);
	 TIMER_stopInterrupt(TIMER_2);
	 TIMER_start(TIMER_2);
	 TIMER_setTime(TIMER_2, 10000);
	 LCD_PinsInit();
	 LCD_Init();
 } 
 
 void I2C_TEST (void)
 {
	 u8 data;
	 if (I2C_start()==EVENT_OK)
	 {
		 LCD_WriteString("start I2C_1");
		 
		 if ( I2C_address_select(0x10,read)==SLA_R_ACK_SENT)
		 {
			 if(I2C_data_rw(&data,read,NACK)==DATA_READ_NACK_SENT)
			 {
				 LCD_SetCursor(1,0);
				 LCD_WriteString("stop I2C_1");
				 I2C_stop();
			 }
		 }
	 }
	 
	 if (I2C_start()==EVENT_OK)
	 {
		 if ( I2C_address_select(0x10,write)==SLA_W_ACK_SENT)
		 {        LCD_Clear();
			 LCD_WriteString("start I2C_2");
			 if(I2C_data_rw(&data,write,ACK)==DATA_WRITE_ACK_SENT)
			 {
				 LCD_SetCursor(1,0);
				 LCD_WriteString("stop  I2C_2");
				 I2C_stop();
			 }
		 }
	 }
	 
	 while(1)
	 {
		 
	 }
 }