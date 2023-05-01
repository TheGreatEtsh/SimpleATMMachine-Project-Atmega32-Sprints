/*
 * app.c
 *
 * Created: 5/1/2023 3:05:07 PM
 *  Author: Ahmed Hesham
 */ 
#include "app.h"








u8 buttonState = 0, pressingCounter = 0;




void APP_init (void)
{
	/*step 1 -> initialize Timer & External Interrupt & SPI*/
	TIMER_init(TIMER_2);
	
	/*step 2 -> initialize LCD & Keypad & Buzzer & Enter\Zero button*/
	BUTTON_init(BUTTON_1_PORT, BUTTON_1_Pin);
	
	/*step 3 -> initialize set buttonFunction as a call back function to external interrupt*/
	
}

void APP_superLoop (void)
{
	
	while (1)
	{
		/*step 1 -> Welcome message is displayed for 1s "Welcome to ATM"*/
		
		/*step 2 -> "Insert a Card" message is displayed in the first line*/

		/*step 3 -> BLOCKED_STATE till interrupt triggered which tiggers PIN_STATE*/
		
		/*step 4 -> "Enter Your Pin" message is displayed in the first line*/
		
		/*step 5 -> Waiting for the input from the keypad and type it in '****' format in the second line*/
		
		/*step 6 -> Pin is only 4 numeric characters*/
		
		/*step 7 -> Pressing the Zero\Enter button for 2s will get the card details from card*/	
		
		/*step 8 -> validate the pin*/
		
		/*step 9 -> if wrong go to step 4, trails are 2*/
		
		/*step 10 -> if trails exceeded go to ALARM_STATE*/	
		
		/*step 11 -> If correct go to WITHDRAWL_STATE*/
		
		/*step 12 -> "Enter Amount"  is displayed in the first line*/
		
		/*step 12 -> input your withdrawal using keypad and written in the form of 0000.00*/
		
		/*step 13 -> Press the Zero\Enter button for 2 secs to accept funds*/
		
		/*step 14 -> Check on the card data*/
		
		/*step 15 -> if failed prints "This is a fraud card" if card pan is not found + Alarm
									  "This card is stolen" if the card is blocked + Alarm
									  "Maximum Limit is Exceeded" if the required amount exceeds the maximum amount limit
									  "Insufficient fund" if the account balance is lower than the required balance.*/
		
		/*step 16 -> If correct print "Approved transaction" for 1s*/
		
		/*step 17 -> print "Remaining balance: 0000.00" for 1s*/
		
		/*step 18 -> print "Ejecting Card" for 1s*/
		
		/*step 19 -> Send a massage to card ecu to start*/
		
		/*step 20 -> go to RESETTING_STATE*/
		
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
				pressingCounter = 0;
			}
		}
	}
}


void	stillPressed(void)
{
	pressingCounter++;
}