/*
 * dio.c
 *
 * Created: 4/3/2023 4:15:37 PM
 *  Author: Ahmed Hesham
 */ 

#include "dio.h"

/******************************************************************************
* \Syntax          : en_dioError_t DIO_init(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 u8_a_direction)
* \Description     : Initializes DIO pins’ direction, output current.
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : u8_a_portNumber	port number used
*					 u8_a_pinNumber		pin number used
*					 u8_a_direction		direction of the pin 
* \Parameters (out): None
* \Return value:   : en_dioError_t		DIO_OK	
*										WRONG_PIN_NUMBER
*										WRONG_PORT_NUMBER
*										WRONG_DIRECTION
*******************************************************************************/

en_dioError_t DIO_init(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 u8_a_direction)	// Initialize dio direction
{
	en_dioError_t error = DIO_OK;
	if (u8_a_pinNumber < 8)
	{
		
		switch(u8_a_direction)
		{
			case INPUT:
			switch(u8_a_portNumber)
			{
				case PORT_A:	DDRA &= ~ (1<<u8_a_pinNumber);	break;
				case PORT_B:	DDRB &= ~ (1<<u8_a_pinNumber);	break;
				case PORT_C:	DDRC &= ~ (1<<u8_a_pinNumber);	break;
				case PORT_D:	DDRD &= ~ (1<<u8_a_pinNumber);	break;
				default:		error = WRONG_PORT_NUMBER;	break;
			}
			break;
			
			case OUTPUT:
			switch(u8_a_portNumber)
			{
				case PORT_A:	DDRA |= (1<<u8_a_pinNumber);		break;
				case PORT_B:	DDRB |= (1<<u8_a_pinNumber);		break;
				case PORT_C:	DDRC |= (1<<u8_a_pinNumber);		break;
				case PORT_D:	DDRD |= (1<<u8_a_pinNumber);		break;
				default:		error = WRONG_PORT_NUMBER;	break;
			}
			break;
			
			default:
			error = WRONG_DIRECTION;
			break;
		}
		
	}
	else
	{
		error = WRONG_PIN_NUMBER;
	}
	return error;
}


/******************************************************************************
* \Syntax          : en_dioError_t DIO_write(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 u8_a_value)
* \Description     : Write on DIO pins’ a specific output High or Low.
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : u8_a_portNumber	port number used
*					 u8_a_pinNumber		pin number used
*					 u8_a_value			output value on the pin
* \Parameters (out): None
* \Return value:   : en_dioError_t		DIO_OK
*										WRONG_PIN_NUMBER
*										WRONG_PORT_NUMBER
*										WRONG_VALUE
*******************************************************************************/

en_dioError_t DIO_write(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 u8_a_value)		// Write data to dio
{
	en_dioError_t error = DIO_OK;
	if (u8_a_pinNumber < 8)
	{
		switch(u8_a_value)
		{
			case LOW:
			switch(u8_a_portNumber)
			{
				case PORT_A:	PORTA &= ~ (1<<u8_a_pinNumber);		break;
				case PORT_B:	PORTB &= ~ (1<<u8_a_pinNumber);		break;
				case PORT_C:	PORTC &= ~ (1<<u8_a_pinNumber);		break;
				case PORT_D:	PORTD &= ~ (1<<u8_a_pinNumber);		break;
				default:		error = WRONG_PORT_NUMBER;		break;
			}
			break;
				
			case HIGH:
			switch(u8_a_portNumber)
			{
				case PORT_A:	PORTA |= (1<<u8_a_pinNumber);		break;
				case PORT_B:	PORTB |= (1<<u8_a_pinNumber);		break;
				case PORT_C:	PORTC |= (1<<u8_a_pinNumber);		break;
				case PORT_D:	PORTD |= (1<<u8_a_pinNumber);		break;
				default:		error = WRONG_PORT_NUMBER;		break;
			}
			break;
				
			default:
				error = WRONG_VALUE;
				break;
		}
	}
	else
	{
		error = WRONG_PIN_NUMBER;
	}
	return error;

}


/******************************************************************************
* \Syntax          : en_dioError_t DIO_toggle(u8 u8_a_portNumber, u8 u8_a_pinNumber)
* \Description     : Toggle the output of a specific pin.
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : u8_a_portNumber	port number used
*					 u8_a_pinNumber		pin number used
* \Parameters (out): None
* \Return value:   : en_dioError_t		DIO_OK
*										WRONG_PIN_NUMBER
*										WRONG_PORT_NUMBER
*******************************************************************************/
en_dioError_t DIO_toggle(u8 u8_a_portNumber, u8 u8_a_pinNumber)						// Toggle dio
{
	en_dioError_t error = DIO_OK;
	if (u8_a_pinNumber < 8)
	{
		switch(u8_a_portNumber)
		{
			case PORT_A:	TGL_BIT(PORTA,u8_a_pinNumber);		break;
			case PORT_B:	TGL_BIT(PORTB,u8_a_pinNumber);		break;
			case PORT_C:	TGL_BIT(PORTC,u8_a_pinNumber);		break;
			case PORT_D:	TGL_BIT(PORTD,u8_a_pinNumber);		break;
			default:		error = WRONG_PORT_NUMBER;		break;
		}	
	}
	else
	{
		error = WRONG_PIN_NUMBER;
	}
	return error;
}


/******************************************************************************
* \Syntax          : en_dioError_t DIO_read(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 *u8_a_value)
* \Description     : Read input from a pin and send it back in a pointer to uint8_t
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : u8_a_portNumber	port number used
*					 u8_a_pinNumber		pin number used
* \Parameters (out): u8_a_value			input value will be returned in that parameter
* \Return value:   : en_dioError_t		DIO_OK
*										WRONG_PIN_NUMBER
*										WRONG_PORT_NUMBER
*******************************************************************************/
en_dioError_t DIO_read(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 *u8_a_value)		// Read dio
{
	en_dioError_t error = DIO_OK;
	if (u8_a_pinNumber < 8)
	{

		switch(u8_a_portNumber)
		{
			case PORT_A:	*u8_a_value = GET_BIT(PINA,u8_a_pinNumber);		break;
			case PORT_B:	*u8_a_value = GET_BIT(PINB,u8_a_pinNumber);		break;
			case PORT_C:	*u8_a_value = GET_BIT(PINC,u8_a_pinNumber);		break;
			case PORT_D:	*u8_a_value = GET_BIT(PIND,u8_a_pinNumber);		break;
			default:		error = WRONG_PORT_NUMBER;				break;
		}
	}
	else
	{
		error = WRONG_PIN_NUMBER;
	}
	return error;
}


/******************************************************************************
* \Syntax          : en_dioError_t DIO_pinPullUp(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 pullUpState)
* \Description     : Disables/enables a pull up resistor to a specific input pin 
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : u8_a_portNumber	port number used
*					 u8_a_pinNumber		pin number used
* \Parameters (out): None
* \Return value:   : en_dioError_t		DIO_OK
*										WRONG_PIN_NUMBER
*										WRONG_PORT_NUMBER
*										WRONG_VALUE
*******************************************************************************/
en_dioError_t DIO_pinPullUp(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 pullUpState)
{
	en_dioError_t error = DIO_OK;
	if (u8_a_pinNumber < 8)
	{
		switch(pullUpState)
		{
			case PULLUP_DISABLE:
			switch(u8_a_portNumber)
			{
				case PORT_A:	CLR_BIT(PORTA, u8_a_pinNumber);		break;
				case PORT_B:	CLR_BIT(PORTB, u8_a_pinNumber);		break;
				case PORT_C:	CLR_BIT(PORTC, u8_a_pinNumber);		break;
				case PORT_D:	CLR_BIT(PORTD, u8_a_pinNumber);		break;
				default:		error = WRONG_PORT_NUMBER;			break;
			}
			break;
			
			case PULLUP_ENABLE:
			switch(u8_a_portNumber)
			{
				case PORT_A:	SET_BIT(PORTA, u8_a_pinNumber);		break;
				case PORT_B:	SET_BIT(PORTB, u8_a_pinNumber);		break;
				case PORT_C:	SET_BIT(PORTC, u8_a_pinNumber);		break;
				case PORT_D:	SET_BIT(PORTD, u8_a_pinNumber);		break;
				default:		error = WRONG_PORT_NUMBER;		break;
			}
			break;
			
			default:
			error = WRONG_VALUE;
			break;
		}
	}
	else
	{
		error = WRONG_PIN_NUMBER;
	}
	return error;

}