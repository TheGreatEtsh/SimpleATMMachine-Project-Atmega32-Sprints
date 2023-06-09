/*
 * app.c
 *
 * Created: 5/1/2023 3:05:07 PM
 *  Author: Ahmed Hesham
 */ 
#include "app.h"






extern ST_accountsDB_t accountsDB[DB_SIZE] ;

u8 buttonState, pressingCounter;
u8 atmState = RESETTING_STATE;




void APP_init (void)
{
	/*step 1 -> initialize Timer & External Interrupt & SPI*/
	TIMER_init(TIMER_2);
	TIMER_stopInterrupt(TIMER_2);
	//TIMER_setTime(100);
	TIMER_start(TIMER_2);
	
	EXTINT_init(INT_0);
	
	SPI_initSlave();
	
	/*step 2 -> initialize LCD & Keypad & Buzzer & Enter\Zero button*/
	LCD_PinsInit();
	LCD_Init();
	BUTTON_init(BUTTON_1_PORT, BUTTON_1_Pin); 
	BUZZER_init(BUZZER_0);
	KEYPAD_init();
	
	/*step 3 -> initialize set buttonFunction as a call back function to external interrupt*/
	EXTINT_setCallBackInt(INT_0, atmTriggered);
	TIMER_setCallBack(TIMER_2, stillPressed);
	
	
	while (SPI_transmitByte(0x55) != 0xAA)
	TIMER_delay(TIMER_2,10);
	
	while (SPI_transmitByte(0x55) != 0xAA)
	TIMER_delay(TIMER_2,10);
	
	while (SPI_transmitByte(0x55) != 0xAA)
	TIMER_delay(TIMER_2,10);
	
}

void APP_superLoop (void)
{
	u8 keyPressed = 0, counter = 0, byteReceived = 0, trials = 0, digits = 0, location = 0;
	f32 amountEntered = 1, remainingBalance = 0;
	u32 copy = 0;
	u8 transAmount[9] = {"00000.00"} ;
	u8 pinEntered[5] = {0};

	ST_cardData_t cardHolderData = {{0,0}};
	EN_transState_t transState = APPROVED;
	
	while (1)
	{
		switch (atmState)		
		{
			case RESETTING_STATE:
			/*step 1 -> Welcome message is displayed for 1s "Welcome to ATM"*/
			LCD_Clear();
			LCD_WriteString("Welcome to ATM");
			TIMER_delay(TIMER_2, 1000);
			LCD_Clear();
			/*step 2 -> "Insert a Card" message is displayed in the first line*/
			LCD_WriteString("Insert a Card");
			//TIMER_delay(TIMER_2, 1000);
			
			/*step 3 -> BLOCKED_STATE till interrupt triggered which tiggers PIN_STATE*/
			atmState = BLOCKED_STATE;
			break;
			
			case BLOCKED_STATE:
			/*DO NOTHING*/
			break;
			
			/*step 4 -> "Enter Your Pin" message is displayed in the first line*/
			case PIN_STATE:
			LCD_Clear();
			LCD_WriteString("Enter Your Pin");
			
			/*step 5 -> Waiting for the input from the keypad and type it in '****' format in the second line*/
			LCD_SetCursor(1,0);
			keyPressed = KEYPAD_read();
			
			/*step 6 -> Pin is only 4 numeric characters*/
			counter = 0;
			while(counter < 4)
			{
				keyPressed = KEYPAD_read();
				if (keyPressed)
				{
					LCD_WriteChar("*");
					pinEntered[counter] = keyPressed;
					counter ++;
				}
				
				BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
				
				if (buttonState)
				{
					TIMER_delay(TIMER_2, 60);
					BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
					if (buttonState)
					{
						while (buttonState)
						{
							BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
						}
						
						LCD_WriteChar("*");
						pinEntered[counter] = '0';
						counter++;
					}
				}
				
			
			}
			
			/*step 7 -> Pressing the Zero\Enter button for 2s will get the card details from card*/
		
			while( atmState == PIN_STATE)			
			{
				
				//pressingCounter = 0;
				BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
				if (buttonState)
				{
					TIMER_delay(TIMER_2, 60);
					BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
					if (buttonState)
					{
						TIMER_setTime(TIMER_2,100);
						TIMER_start(TIMER_2);
						TIMER_enableInterrupt(TIMER_2);
						while (buttonState)
						{
							BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
						}
						if (pressingCounter >= 10)
						{
							atmState = VALIDATING_PIN_STATE;
							
						}
						else
						{
							/*DO NOTHING*/
						}
						TIMER_stopInterrupt(TIMER_2);
						TIMER_stop(TIMER_2);
						pressingCounter = 0;
					}
				}
			}
			
			break;
			
			case RECEIVING_STATE:
			LCD_Clear();
			LCD_WriteString("Receiving");
			TIMER_delay(TIMER_2,1000);
			
			counter = 0;
			while (SPI_transmitByte(0xDD) != 0xDD)
			TIMER_delay(TIMER_2,10);
			
			while (counter < 20)
			{
				byteReceived  = SPI_transmitByte(0xBB);
				if (byteReceived >= '0' || byteReceived <= '9')
				{
					if (counter)
					{
						cardHolderData.primaryAcountNumber[counter-1] = byteReceived;
						
					}
					counter++;
					
				}
				else if (byteReceived == 0)
				{
					break;
				}
				
				byteReceived = 255;
				
				TIMER_delay(TIMER_2,10);
				
			}
			cardHolderData.primaryAcountNumber[counter] = 0;
			
			counter = 0;
			byteReceived = 255;
			
			while (SPI_transmitByte(0xDD) != 0xDD)
			TIMER_delay(TIMER_2,10);
			
			
			while (counter < 5)
			{
				byteReceived  = SPI_transmitByte(0xCC);
				if (byteReceived >= '0' || byteReceived <= '9')
				{

					if (counter)
					{
						cardHolderData.PIN[counter-1] = byteReceived;
						
					}
					counter++;
					
				}
				else if (byteReceived == 0)
				{
					break;
				}
				
				byteReceived = 255;
				
				TIMER_delay(TIMER_2,10);
				
			}
			cardHolderData.PIN[5] = 0;
			
			//LCD_Clear();
			//LCD_WriteString(cardHolderData.primaryAcountNumber);
			//LCD_SetCursor(1,0);
			//LCD_WriteString(cardHolderData.PIN);
			//TIMER_delay(TIMER_2, 5000);
			
			
			atmState = PIN_STATE;
			
			break;
			
			
			
			/*step 8 -> validate the pin*/
			case VALIDATING_PIN_STATE:
			
			counter = 0;
			while (counter < 4)
			{
				if(pinEntered[counter] == cardHolderData.PIN [counter])
				{
					counter ++;	
				}
				else
				{
					break;
				}
			}

			
			/*step 9 -> if wrong go to step 4, trails are 2*/
			if (counter != 4)
			{
				atmState = PIN_STATE;
				trials++;
			/*step 10 -> if trails exceeded go to ALARM_STATE*/
				if (trials > 2)
				{
					atmState = ALARM_STATE;
				}
			}
			/*step 11 -> If correct go to WITHDRAWL_STATE*/
			else
			{
				atmState = WITHDRAWL_STATE;
				transAmount[0] = '0';
				transAmount[1] = '0';
				transAmount[2] = '0';
				transAmount[3] = '0';
				transAmount[4] = '0';
				transAmount[5] = '.';
				transAmount[6] = '0';
				transAmount[7] = '0';
				amountEntered = 1;
				digits = 0;
			}
			break;

			/*step 12 -> "Enter Amount"  is displayed in the first line*/
			case WITHDRAWL_STATE:
			
			
			LCD_Clear();
			LCD_WriteString("Enter Amount");
			/*step 12 -> input your withdrawal using keypad and written in the form of 0000.00*/
			LCD_SetCursor(1,0);
			LCD_WriteString(transAmount);

			keyPressed = 0;
			
			keyPressed = KEYPAD_read();
			
			counter	= 0;

			
			while (keyPressed == 0)
			{
				LCD_SetCursor(1,0);
				
				keyPressed = KEYPAD_read();
				if (keyPressed)
				{
					if (digits)
					{
						amountEntered *= 10;
						amountEntered += (keyPressed - 48);
						copy = amountEntered;
						digits ++;
						
					}
					else
					{
						
						amountEntered *= (keyPressed - 48);
						copy = amountEntered;
						digits++;
					}
					
					for (counter = 0; counter < digits; counter++)
					{
						location = 7 - counter;
						if (location > 5)
						{
							transAmount[7-counter] = (copy%10) + 48;
							copy/=10;
						}
						else
						{
							transAmount[7-counter-1] = (copy%10) + 48;
							copy/=10;
						}
						
					}
					
					transAmount[7] = keyPressed;
				}

				BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
				if (buttonState)
				{
					TIMER_delay(TIMER_2, 60);
					BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
					if (buttonState)
					{
						pressingCounter = 0;
						TIMER_setTime(TIMER_2,100);
						TIMER_start(TIMER_2);
						TIMER_enableInterrupt(TIMER_2);
						while (buttonState)
						{
							BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
						}
						keyPressed = 1;
						if (pressingCounter >= 10)
						{
							/*amount accepted*/
							amountEntered /= 100;
							atmState = CHECKING_STATE;
							
						}
						else
						{
							TIMER_stopInterrupt(TIMER_2);
							if (digits)
							{
								amountEntered *= 10;
								copy = amountEntered;
								digits ++;
								
							}
							else
							{
								/*DO NOTHING*/
							}
							
							for (counter = 0; counter < digits; counter++)
							{
								location = 7 - counter;
								if (location > 5)
								{
									transAmount[7-counter] = (copy%10) + 48;
									copy/=10;
								}
								else
								{
									transAmount[7-counter-1] = (copy%10) + 48;
									copy/=10;
								}
								
							}
							
							transAmount[7] = '0';
						}
						TIMER_stopInterrupt(TIMER_2);
						TIMER_stop(TIMER_2);
						pressingCounter = 0;
					}
				}
				
				
				
			}
			
			break;		
			
			/*step 14 -> Check on the card data*/
			case CHECKING_STATE:
			if(amountEntered == 0.01)
			{
				amountEntered = 0;
			}
			transState = SERVER_recieveTransactionData(&remainingBalance, amountEntered, &cardHolderData);
			amountEntered = 1;
			/*step 15 -> if failed prints "This is a fraud card" if card pan is not found + Alarm
										  "This card is stolen" if the card is blocked + Alarm
										  "Maximum Limit is Exceeded" if the required amount exceeds the maximum amount limit
										  "Insufficient fund" if the account balance is lower than the required balance.*/
			if (transState == FRAUD_CARD)
			{
				LCD_Clear();
				LCD_WriteString("This is a ");
				LCD_SetCursor(1,0);
				LCD_WriteString("fraud card");
				TIMER_delay(TIMER_2,1000);
				atmState = ALARM_STATE;
			}
			else if (transState == DECLINED_STOLEN_CARD)
			{
				LCD_Clear();
				LCD_WriteString("This card is");
				LCD_SetCursor(1,0);
				LCD_WriteString("stolen");
				TIMER_delay(TIMER_2,1000);
				atmState = ALARM_STATE;
			}
			else if (transState == EXCEEDED_MAXIMUM_AMOUNT)
			{
				LCD_Clear();
				LCD_WriteString("Maximum Limit is");
				LCD_SetCursor(1,0);
				LCD_WriteString("Exceeded");
				TIMER_delay(TIMER_2,1000);
				atmState = EJECTING_CARD_STATE;
			}
			else if (transState == DECLINED_INSUFFECIENT_FUND)
			{
				LCD_Clear();
				LCD_WriteString("Insufficient");
				LCD_SetCursor(1,0);
				LCD_WriteString("fund");
				TIMER_delay(TIMER_2,1000);
				atmState = EJECTING_CARD_STATE;
			}
			/*step 16 -> If correct print "Approved transaction" for 1s*/
			else if(transState == APPROVED)
			{
				LCD_Clear();
				LCD_WriteString("Approved ");
				LCD_SetCursor(1,0);
				LCD_WriteString("transaction");
				TIMER_delay(TIMER_2, 1000);
				atmState = PRINTING_BALANCE_STATE;
			}
			break;
			
			/*step 17 -> print "Remaining balance: 0000.00" for 1s*/
			case PRINTING_BALANCE_STATE:
			remainingBalance*=100;
			copy = remainingBalance;
			
			LCD_Clear();
			LCD_WriteString("Remaining Balance");
			LCD_SetCursor(1,0);
			for (counter = 0; counter < 7; counter++)
			{
				location = 7 - counter;
				if (location > 5)
				{
					transAmount[7-counter] = (copy%10) + 48;
					copy/=10;
					if (copy == 0)
					{
						break;
					}
				}
				else
				{
					transAmount[7-counter-1] = (copy%10) + 48;
					copy/=10;
					if (copy == 0)
					{
						break;
					}
				}
			}
			LCD_WriteString(transAmount);
			TIMER_delay(TIMER_2, 1000);
			
			atmState = EJECTING_CARD_STATE;
			break;
			
			
			/*step 18 -> print "Ejecting Card" for 1s*/
			case EJECTING_CARD_STATE:
			LCD_Clear();
			LCD_WriteString("Ejecting Card");
			TIMER_delay(TIMER_2,1000);
			
			/*step 19 -> Send a massage to card ecu to start*/
			
			while(SPI_transmitByte(0xDD) != 0xDD)
			TIMER_delay(TIMER_2,10);
			
			/*step 20 -> go to RESETTING_STATE*/
			atmState = RESETTING_STATE;
			break;
			
			case ALARM_STATE:
			LCD_Clear();
			LCD_WriteString("ALARM");
			
			BUZZER_on(BUZZER_0);
			EXTINT_setCallBackInt(INT_0,doNothing);
			
			
			break;
			
		}
	}
}

void APP_buttonTest(void)
{
	TIMER_init(TIMER_2);
	TIMER_stopInterrupt(TIMER_2);
	TIMER_start(TIMER_2);
	TIMER_setCallBack(TIMER_2, stillPressed);
	DIO_init(PORT_D,6,OUTPUT);
	DIO_init(PORT_D,7,OUTPUT);
	while(1)
	{
		BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
		if (buttonState)
		{
			TIMER_delay(TIMER_2, 60);
			BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
			if (buttonState)
			{
				TIMER_setTime(TIMER_2,100);
				TIMER_start(TIMER_2);
				TIMER_enableInterrupt(TIMER_2);
				while (buttonState)
				{
					BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
				}
				if (pressingCounter >= 20)
				{
					/*toggle pin 1*/
					DIO_toggle(PORT_D,6);
				}
				else
				{
					/*toggle pin 2*/
					DIO_toggle(PORT_D,7);
				}
				TIMER_stopInterrupt(TIMER_2);
				TIMER_stop(TIMER_2);
				pressingCounter = 0;
			}
		}
	}
}


void APP_lcdTEST()
{
	
	u8 keyPressed = 0, digits = 0, counter = 0;
	f32 amountEntered = 1; 
	u32 copy = 0;
	u8 transAmount[9] = {"00000.00"} ;
	u8 location = 0;	
	
	TIMER_init(TIMER_2);
	TIMER_stopInterrupt(TIMER_2);
	TIMER_start(TIMER_2);
	TIMER_setCallBack(TIMER_2, stillPressed);
	
	LCD_PinsInit();
	LCD_Init();
	
	KEYPAD_init();
	
	//BUTTON_init(BUTTON_1_PORT, BUTTON_1_Pin);
	DIO_init(PORT_D,6,OUTPUT);
	DIO_init(PORT_D,7,OUTPUT);
	
	while(1)
	{
		LCD_Clear();
		LCD_WriteString("Enter Amount");
		//LCD_WriteNumber(amountEntered);
		
		LCD_SetCursor(1,0);
		LCD_WriteString(transAmount);

		keyPressed = KEYPAD_read();
		
		counter	= 0;
		 
		while (keyPressed == 0)
 		{
 			LCD_SetCursor(1,0);
 			
 			keyPressed = KEYPAD_read();
 			if (keyPressed)
 			{
 				if (digits)
 				{
 					amountEntered *= 10;
 					amountEntered += (keyPressed - 48);
					copy = amountEntered;
 					digits ++;
 					
 				}
 				else
 				{
					
 					amountEntered *= (keyPressed - 48);
					copy = amountEntered; 
 					digits++;
 				}
 				
 				
 				
 				
 				for (counter = 0; counter < digits; counter++)
 				{
  					location = 7 - counter;
  					if (location > 5)
  					{
  						transAmount[7-counter] = (copy%10) + 48;
  						copy/=10;
  					}
  					else
  					{
						transAmount[7-counter-1] = (copy%10) + 48;
						copy/=10;
					}
					
 				}
 	
 				transAmount[7] = keyPressed;
 			}

			BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
			if (buttonState)
			{
				TIMER_delay(TIMER_2, 60);
				BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
				if (buttonState)
				{
					pressingCounter = 0;
					TIMER_setTime(TIMER_2,100);
					TIMER_start(TIMER_2);
					TIMER_enableInterrupt(TIMER_2);
					while (buttonState)
					{
						BUTTON_read(BUTTON_1_PORT, BUTTON_1_Pin, &buttonState);
					}
					keyPressed = 1;
					if (pressingCounter >= 10)
					{
						/*toggle pin 1*/
						DIO_toggle(PORT_D,6);
						/*amount accepted*/
						amountEntered /= 100;
						//atmState = CHECKING_STATE;
						
					}
					else
					{
						TIMER_stopInterrupt(TIMER_2);
						/*toggle pin 2*/
						DIO_toggle(PORT_D,7);
 						if (digits)
 						{
 							amountEntered *= 10;
 							copy = amountEntered;
 							digits ++;
 							
 						}
 						else
 						{
 							/*DO NOTHING*/
 						}
 						 							
 						for (counter = 0; counter < digits; counter++)
 						{
 							location = 7 - counter;
 							if (location > 5)
 							{
 								transAmount[7-counter] = (copy%10) + 48;
 								copy/=10;
 							}
 							else
 							{
 								transAmount[7-counter-1] = (copy%10) + 48;
 								copy/=10;
 							}
 							
 						}
 						
 						transAmount[7] = '0';
					}
					TIMER_stopInterrupt(TIMER_2);
					TIMER_stop(TIMER_2);
					pressingCounter = 0;
				}
			}
						
  				
 				
 		}
 			
 	
	}
}

void APP_spiSlaveTest (void)
{
	TIMER_init(TIMER_2);
	TIMER_stopInterrupt(TIMER_2);
	TIMER_start(TIMER_2);

	
	LCD_PinsInit();
	LCD_Init();
	
	SPI_initSlave();
	
	u8 recievedData = 0;
	recievedData = SPI_transmitByte(0x0F);
	LCD_WriteNumber(recievedData);

	while(1)
	{
		recievedData = SPI_transmitByte(0x0F);
		LCD_WriteNumber(recievedData);
		
	}
}

void	stillPressed(void)
{
	pressingCounter++;
}

void	atmTriggered(void)
{
	atmState = RECEIVING_STATE;
}

void doNothing(void)
{
	while (1)
	{
	}
}

void APP_comTesting (void)
{
	u8 counter = 0, byteReceived = 0;
	//u8 keyPressed = 0, counter = 0, byteReceived = 0, trials = 0, digits = 0, location = 0;
	//f32 amountEntered = 1, remainingBalance = 0;
	//u32 copy = 0;
	//u8 transAmount[9] = {"00000.00"} ;
	//u8 pinEntered[5] = {0};

	ST_cardData_t cardHolderData = {{0,0}};
	//EN_transState_t transState = APPROVED;
	
	TIMER_init(TIMER_2);
	TIMER_stopInterrupt(TIMER_2);
	TIMER_start(TIMER_2);

	
	LCD_PinsInit();
	LCD_Init();
	
//	LCD_WriteString("Hello World");
	
	SPI_initSlave();
	
	
	while (SPI_transmitByte(0x55) != 0xAA)
	TIMER_delay(TIMER_2,10);
	
	while (SPI_transmitByte(0x55) != 0xAA)
	TIMER_delay(TIMER_2,10);
	
	while (1)
	{
		LCD_Clear();
		LCD_WriteString("Receiving");
		TIMER_delay(TIMER_2,1000);
		LCD_Clear();
		counter = 0;
		while (SPI_transmitByte(0x55) == 0)
		TIMER_delay(TIMER_2,10);
		while (counter < 20)
		{
			byteReceived  = SPI_transmitByte(0xBB);
			if (byteReceived >= '0' || byteReceived <= '9')
			{
				//LCD_WriteChar(byteReceived);
				//if (counter)
				cardHolderData.primaryAcountNumber[counter] = byteReceived;
				counter++;
				
			}
			else if (byteReceived == 0)
			{
				break;
			}
			
			byteReceived = 255;
			
			TIMER_delay(TIMER_2,10);
			
		}

// 		while (counter < 19)
// 		{
// 			//cardHolderData.primaryAcountNumber[counter] = accountsDB[0].primaryAccountNumber[counter];
// 	
// 			byteReceived  = SPI_transmitByte(0xBB);
// 			TIMER_delay(TIMER_2,10);
// 			if(byteReceived >= '0' || byteReceived <= '9')
// 			//if (byteReceived)
// 			{
// 				//if (counter)
// 				//{
// 					cardHolderData.primaryAcountNumber[counter] = byteReceived;
// 					
// 				//}
// 				//else
// 				//{
// 				//	
// 				//}
// 				
// 				//LCD_WriteNumber(counter);
// 				LCD_WriteChar(byteReceived);
// 				
// 				counter++;
// 			}
// 			else if (byteReceived == 0)
// 			{
// 				break;
// 			}
// 			byteReceived = 255;
// 		}
		cardHolderData.primaryAcountNumber[counter] = 0;
		
		
		//LCD_WriteString(cardHolderData.primaryAcountNumber);
		//TIMER_delay(TIMER_2,1000);
		//LCD_SetCursor(1,0);
		counter = 0;
		byteReceived = 255;
		
		while (SPI_transmitByte(0x55) == 0)
		TIMER_delay(TIMER_2,10);
		while (counter < 5)
		{
			byteReceived  = SPI_transmitByte(0xCC);
			if (byteReceived >= '0' || byteReceived <= '9')
			{
				//LCD_WriteChar(byteReceived);
				//if (counter)
				cardHolderData.PIN[counter] = byteReceived;
				counter++;
				
			}
			else if (byteReceived == 0)
			{
				break;
			}
			
			byteReceived = 255;
			
			TIMER_delay(TIMER_2,10);
			
		}
		//TIMER_delay(TIMER_2, 2000);
		cardHolderData.PIN[5] = 0;
		
		
		LCD_WriteString(cardHolderData.primaryAcountNumber);
		LCD_SetCursor(1,0);
		LCD_WriteString(cardHolderData.PIN);
		TIMER_delay(TIMER_2, 5000);
		
		
	}
	
}