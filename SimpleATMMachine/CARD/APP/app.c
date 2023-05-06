/*
 * app.c
 *
 * Created: 5/1/2023 3:00:37 PM
 *  Author: Ahmed Hesham
 */ 
#include "app.h"

u8 cardMode = 0, programmingState = 0, userState = 0; 
void APP_init(void)
{
	TIMER_init(TIMER_2);
	TIMER_stopInterrupt(TIMER_2);
	TIMER_start(TIMER_2);
	
	LCD_PinsInit();
	LCD_Init();
	
	TRIGGER_init();
	
	
	
	EEPROM_init();
	TIMER_delay(TIMER_2, 100);
	
	UART_Init();
	TIMER_delay(TIMER_2, 100);
	
	SPI_initMaster();	
	TIMER_delay(TIMER_2, 100);
	SPI_startTransmission();
	
	while (SPI_transmitByte(0xAA) != 0x55)
	TIMER_delay(TIMER_2,10);
	
	while (SPI_transmitByte(0xAA) != 0x55)
	TIMER_delay(TIMER_2,10);
	
	TIMER_delay(TIMER_2, 100);
}

void APP_superLoop(void)
{
	/*Step 1 -> if eeprom is empty goto PROGRAMMING_MODE*/
	u8 checkEEPROM = EEPROM_EMPTY, buffer = 0, counter = 0, true = 0;
	
	u8 PAN [21]			= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	u8 PIN [6]			= {0,0,0,0,0,0};
	u8 PINCopy [6]		= {0,0,0,0,0,0};
	checkEEPROM = APP_checkEEPROM();
	
	if (checkEEPROM == EEPROM_NOT_EMPTY)
	{
		cardMode = USER_MODE;
	}
	else
	{
		cardMode = PROGRAMMING_MODE;
	}
	
	/*Step 2 -> if not choose between PROGRAMMING_MODE '2' & USER_MODE = '1'*/
	while (1)	
	{	
		switch(cardMode)
		{
			case PROGRAMMING_MODE:
			switch (programmingState)
			{
				/*Step 3 -> in PROGRAMMING_MODE step 1 -> Send on UART "Please Enter Card PAN"*/
				case PRO_INITIAL_STATE:
				UART_sendString("Please Enter Card PAN\r");
				
				
				/*Step 3 -> in PROGRAMMING_MODE step 2 -> wait for the user to enter the PAN till it enters enter through uart*/
				counter = 0;
				buffer = 0;
				while (buffer != '\r')
				{
					
					buffer = UART_GetChar();
					while(buffer >= 48 && buffer <= 57)
					{
						UART_SendChar(buffer);
						PAN[counter] = buffer;
						counter++;
						buffer = 0;
					}
				}
				UART_SendChar('\r');
				TIMER_delay(TIMER_2, 10);
				
				if(counter < 16 || counter > 19)
				{
					UART_sendString("PAN is not correct\r");
					break;
				}
				else
				{
					UART_sendString("PAN is valid\r");
					programmingState = PRO_SAVING_PAN;
					break;
				}
				
				/*Step 3 -> in PROGRAMMING_MODE step 3 -> save PAN in the EEPROM from address 0x0010*/
				case PRO_SAVING_PAN:
				EEPROM_writeString_256(0x10,PAN);
				//LCD_WriteString(PAN);
				programmingState = PRO_RECEIVING_PIN;
				break;
				
				/*Step 3 -> in PROGRAMMING_MODE step 4 -> Send on UART "Please Enter New PIN"*/
				case PRO_RECEIVING_PIN:
				UART_sendString("Please Enter New PIN\rYou can only enter numbers and only 4 digits\r");
				
				/*Step 3 -> in PROGRAMMING_MODE step 5 -> wait for the user to enter the PIN till it enters enter through uart*/
				counter = 0;
				buffer = 0;
				while (counter < 4)
				{	
					buffer = UART_GetChar();
					while(buffer >= 48 && buffer <= 57)
					{
						UART_SendChar('*');
						TIMER_delay(TIMER_2, 10);
						/*Step 3 -> in PROGRAMMING_MODE step 6 -> save PIN in firstCopy*/
						PIN[counter] = buffer;
						counter++;
						buffer = 0;
					}
				}
				UART_SendChar('\r');
				TIMER_delay(TIMER_2, 10);
				
				/*Step 3 -> in PROGRAMMING_MODE step 7 -> Send on UART "Please Confirm New PIN"*/
				UART_sendString("Please Confirm New PIN\r");
				
				/*Step 3 -> in PROGRAMMING_MODE step 8 -> wait for the user to enter the PIN till it enters enter through uart*/
				counter = 0;
				buffer = 0;
				while (counter < 4)
				{
					buffer = UART_GetChar();
					while(buffer >= 48 && buffer <= 57)
					{
						UART_SendChar('*');
						TIMER_delay(TIMER_2, 10);
						/*Step 3 -> in PROGRAMMING_MODE step 9 -> save PIN entered in secondCopy*/
						PINCopy[counter] = buffer;
						counter++;
						buffer = 0;
					}
				}
				UART_SendChar('\r');
				TIMER_delay(TIMER_2, 10);
				
				/*Step 3 -> in PROGRAMMING_MODE step 10 -> compare firstCopy and secondCopy make sure that they are four characters and all numerics"*/
				true = 0;
				
				for(counter = 0; counter < 4; counter++)
				{
					if (PIN[counter] == PINCopy[counter])
					{
						true++;
					}
				}
				
				/*Step 3 -> in PROGRAMMING_MODE step 11 -> if there is a mistake print "Wrong PIN" and got to step 4*/
				if (true != 4)
				{
					UART_sendString("Wrong PIN\r");
					TIMER_delay(TIMER_2, 10);
					
				}
				
				/*Step 3 -> in PROGRAMMING_MODE step 12 -> if matching save PIN -secondCopy- in EEPROM in address 0x0030*/
				else
				{
					EEPROM_writeString_256(PIN_ADDRESS,PIN);
				
					/*Step 3 -> in PROGRAMMING_MODE step 13 -> go to USER_MODE*/
					cardMode = USER_MODE;
				}
				break;	
			}
			break;
			
			/*Step 4 -> in USER_MODE step 1 -> print "Please press 1 for entering user mode and 2 for programming mode"*/
			case USER_MODE:
			UART_sendString("Please press 1 for entering user mode and 2 for programming mode\r");
			
			/*Step 4 -> in USER_MODE step 2 -> recieve operation from UART, neglect if it is not equal '1' or '2'*/
			buffer = 0;
			while (buffer != '1' || buffer != '2')
			{
				buffer = UART_GetChar();
				if (buffer == '1' || buffer == '2')
				{
					UART_SendChar(buffer);
					TIMER_delay(TIMER_2, 10);
					break;
				}
				
			}
			UART_SendChar('\r');
			TIMER_delay(TIMER_2, 10);
			
			
			/*Step 4 -> in USER_MODE step 3 -> If = 1, trigger ATM, send PAN and PIN then IDLE_STATE*/
			if (buffer == '1')
			{
				TRIGGER_triggerMCU();
				EEPROM_readString_256(PAN_ADDRESS, PAN);
				TIMER_delay(TIMER_2, 10);
				
				EEPROM_readString_256(PIN_ADDRESS, PIN);
				TIMER_delay(TIMER_2, 10);
				
				counter = 0;
				while(PAN[counter])
				{
					if(SPI_transmitByte(PAN[counter]) == 0xBB)
					{
						counter++;
					}
					TIMER_delay(TIMER_2, 10);
					
				}
				while(SPI_transmitByte(0) == 0xBB)
				TIMER_delay(TIMER_2,10);
				
				counter = 0;
				while(counter < 4)
				{
					if(SPI_transmitByte(PIN[counter]) == 0xCC)
					{
						counter++;
					}
					TIMER_delay(TIMER_2, 10);
				}
				while(SPI_transmitByte(0) == 0xCC)
				TIMER_delay(TIMER_2,10);
				
				TIMER_delay(TIMER_2,5000);
				while(SPI_transmitByte(0xDD) != 0xDD)
				TIMER_delay(TIMER_2,100);
				
			}
			/*Step 4 -> in USER_MODE step 4 -> If = 2, go to PROGRAMMING_MODE INITIAL_STATE*/
			else if(buffer == '2')
			{
				cardMode = PROGRAMMING_MODE;
				programmingState = PRO_INITIAL_STATE;
			}
			break;
		}
	}
}

void APP_testingEEPROM (void)
{
	TIMER_init(TIMER_2);
	TIMER_stopInterrupt(TIMER_2);
	TIMER_start(TIMER_2);

	
	LCD_PinsInit();
	LCD_Init();
	
	EEPROM_init();
	
	DIO_init(PORT_D,7,OUTPUT);
	DIO_init(PORT_D,6,OUTPUT);
	
	
	u8 recievedData = 0;
	u32 address = 0;
	while(1)
	{
		EEPROM_readByte_256(address, &recievedData);
		LCD_WriteNumber(recievedData);
		
		if(recievedData == 255)
		{
			DIO_write(PORT_D,7,HIGH);
		}
		else
		{
			DIO_write(PORT_D,6,HIGH);
		}
		//TIMER_delay(TIMER_2, 500);
		address++;
	}
}


void APP_deleteAll (void)
{
	for (u32 i = 0; i <= 0xFF ; i++)
	{
		EEPROM_writeByte_256((u16)i,0xFF);
		TIMER_delay(TIMER_2,20);
	}
}

u8 APP_checkEEPROM(void)
{
	u8 dataRecieved = 0;
	for(u8 i = PAN_ADDRESS; i < PIN_ADDRESS + 0x10; i++)
	{
		EEPROM_readByte_256(i, &dataRecieved);
		TIMER_delay(TIMER_2,10);
		if (dataRecieved != 255)
		{
			break;
		}
	}
	
	if(dataRecieved != 255)
	{
		return EEPROM_NOT_EMPTY;
	}
	else
	{
		return EEPROM_EMPTY;
	}
}


void APP_testingUART(void)
{
	u8 buffer = 0;
	
	TIMER_init(TIMER_2);
	TIMER_stopInterrupt(TIMER_2);
	TIMER_start(TIMER_2);

	
	LCD_PinsInit();
	LCD_Init();
	
	UART_Init();
	//UART_sendString("Ahmed");
	
	DIO_init(PORT_D,7,OUTPUT);
	DIO_init(PORT_D,6,OUTPUT);
	
	
	while(1)
	{
 		//buffer = UART_GetChar();
 		// if (buffer == 13)
 		//{
		//	 
		//	 while (1)
		//	 {
		//		 DIO_write(PORT_D,7,HIGH);
		//		 DIO_write(PORT_D,7,HIGH);
		//		 
		//	 }
 		//}
		//UART_SendChar(buffer);	
		
		while (buffer != '\r')
		{
			
			buffer = UART_GetChar();
			while(buffer >= 48 && buffer <= 57)
			{
				UART_SendChar(buffer);
				TIMER_delay(TIMER_2,10);
				buffer = 0;
				
			}
		}

		
		
	}
}