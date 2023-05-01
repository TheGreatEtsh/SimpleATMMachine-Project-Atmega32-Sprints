/*
 * buzzer.c
 *
 * Created: 4/18/2023 5:39:54 AM
 *  Author: Ahmed Hesham
 */ 
												
#include "buzzer.h"
											/*port_#, pin_#*/
st_buzzer_t buzzerDB [NUMBER_OF_BUZZERS] =	{{PORT_B,	 3}};


/******************************************************************************
* \Syntax          : en_buzzerError_t	BUZZER_init		(u8 u8_a_buzzerNumber)
* \Description     : Initialize Buzzer according to preprocessed configured definitions
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : u8_a_buzzerNumber		Buzzer Number Used
* \Parameters (out): None
* \Return value:   : en_buzzerError_t		BUZZER_OK
*											WRONG_BUZZER
*******************************************************************************/	
en_buzzerError_t	BUZZER_init		(u8 u8_a_buzzerNumber)
{
	en_buzzerError_t error = BUZZER_OK;
	if (u8_a_buzzerNumber >= 0 && u8_a_buzzerNumber < NUMBER_OF_BUZZERS)
	{
		DIO_init(buzzerDB[u8_a_buzzerNumber].portNumber, buzzerDB[u8_a_buzzerNumber].pinNumber, OUTPUT);
	}
	else
	{
		error = WRONG_BUZZER;
	}
	
	return error;
}


/******************************************************************************
* \Syntax          : en_buzzerError_t	BUZZER_on		(u8 u8_a_buzzerNumber)
* \Description     : Switches Buzzer On
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : u8_a_buzzerNumber		Buzzer Number Used
* \Parameters (out): None
* \Return value:   : en_buzzerError_t		BUZZER_OK
*											WRONG_BUZZER
*******************************************************************************/
en_buzzerError_t	BUZZER_on		(u8 u8_a_buzzerNumber)
{
	en_buzzerError_t error = BUZZER_OK;
	
	if (u8_a_buzzerNumber >= 0 && u8_a_buzzerNumber < NUMBER_OF_BUZZERS)
	{
		DIO_write(buzzerDB[u8_a_buzzerNumber].portNumber, buzzerDB[u8_a_buzzerNumber].pinNumber, HIGH);
	}
	else
	{
		error = WRONG_BUZZER;
	}
	
	return error;
}


/******************************************************************************
* \Syntax          : en_buzzerError_t	BUZZER_off		(u8 u8_a_buzzerNumber)
* \Description     : Switches Buzzer OFF
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : u8_a_buzzerNumber		Buzzer Number Used
* \Parameters (out): None
* \Return value:   : en_buzzerError_t		BUZZER_OK
*											WRONG_BUZZER
*******************************************************************************/
en_buzzerError_t	BUZZER_off		(u8 u8_a_buzzerNumber)
{
	en_buzzerError_t error = BUZZER_OK;
	if (u8_a_buzzerNumber >= 0 && u8_a_buzzerNumber < NUMBER_OF_BUZZERS)
	{
		DIO_write(buzzerDB[u8_a_buzzerNumber].portNumber, buzzerDB[u8_a_buzzerNumber].pinNumber, LOW);
	}
	else
	{
		error = WRONG_BUZZER;
	}
	
	return error;
}