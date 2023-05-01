/*
 * button.c
 *
 * Created: 4/3/2023 5:52:59 PM
 *  Author: Ahmed Hesham
 */ 
#include "button.h"


en_buttonError_t BUTTON_init(u8 u8_a_buttonPort, u8 u8_a_buttonPin)
{
	en_buttonError_t en_a_error = BUTTON_OK;
	if (u8_a_buttonPort > PORT_D)
	{
		en_a_error = WRONG_BUTTON_PORT;
	}
	else if (u8_a_buttonPin > 7)
	{
		en_a_error = WRONG_BUTTON_PIN;
	}
	else
	{		
		DIO_init(u8_a_buttonPort, u8_a_buttonPin, INPUT);
		en_a_error = BUTTON_OK;
	}
	
	return en_a_error;
}

en_buttonError_t BUTTON_read(u8 u8_a_buttonPort, u8 u8_a_buttonPin, u8 *u8_a_buttonState)
{
	en_buttonError_t en_a_error = BUTTON_OK;
	if (u8_a_buttonPort > PORT_D)
	{
		en_a_error = WRONG_BUTTON_PORT;
	}
	else if (u8_a_buttonPin > 7)
	{
		en_a_error = WRONG_BUTTON_PIN;
	}
	else
	{
		DIO_read(u8_a_buttonPort, u8_a_buttonPin, u8_a_buttonState);
		en_a_error = BUTTON_OK;
	}
	
	return en_a_error;
}