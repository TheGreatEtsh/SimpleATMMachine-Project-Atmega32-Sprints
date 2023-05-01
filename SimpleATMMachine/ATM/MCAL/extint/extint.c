/*
 * extint.c
 *
 * Created: 4/5/2023 4:40:48 PM
 *  Author: Ahmed Hesham
 */ 
#include "ExtInt.h"

void (*EXTINT_0_callBack) (void) = nullPtr;
void (*EXTINT_1_callBack) (void) = nullPtr;
void (*EXTINT_2_callBack) (void) = nullPtr;

en_extintError_t EXTINT_init (u8 u8_a_intNumber)
{
	en_extintError_t en_a_error =EXTINT_OK;
	/* Step 1	->		Choose Sense Control */
	switch(u8_a_intNumber)
	{
		case INT_0:
		#if			SENSE_CONTROL_0		==		LOW_LEVEL
		CLR_BIT(MCUCR,ISC00);
		CLR_BIT(MCUCR,ISC01);
		#elif		SENSE_CONTROL_0		==		ANY_CHANGE
		SET_BIT(MCUCR,ISC00);
		CLR_BIT(MCUCR,ISC01);
		#elif		SENSE_CONTROL_0		==		FALLING_EDGE
		CLR_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);
		#elif		SENSE_CONTROL_0		==		RISING_EDGE
		SET_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);
		#endif
		break;
		
		case INT_1:
		#if			SENSE_CONTROL_1		==		LOW_LEVEL
		CLR_BIT(MCUCR,ISC10);
		CLR_BIT(MCUCR,ISC11);
		#elif		SENSE_CONTROL_1		==		ANY_CHANGE
		SET_BIT(MCUCR,ISC10);
		CLR_BIT(MCUCR,ISC11);
		#elif		SENSE_CONTROL_1		==		FALLING_EDGE
		CLR_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);
		#elif		SENSE_CONTROL_1		==		RISING_EDGE
		SET_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);
		#endif
		break;
		
		case INT_2:
		#if			SENSE_CONTROL_2		==		FALLING_EDGE
		CLR_BIT(MCUCR,ISC2);
		#elif		SENSE_CONTROL_2		==		RISING_EDGE
		SET_BIT(MCUCSR,ISC2);
		#endif
		break;
		
		default: en_a_error = WRONG_INT_NUMBER;
		break;
	}
	/* Step 2	->		Enable Peripheral Interrupt */
	switch(u8_a_intNumber)
	{
		case INT_0:	SET_BIT(GICR,INT0);		break;
		case INT_1:	SET_BIT(GICR,INT1);		break;
		case INT_2:	SET_BIT(GICR,INT2);		break;
		default: en_a_error = WRONG_INT_NUMBER;	break;
	}
	
	
	/* Step 3	->		Enable Global Interrupt */
	SET_BIT(SREG,Ibit);
	
	return en_a_error;
}


void EXTINT_setCallBackInt (u8 u8_a_intNumber, void (*funPtr) (void))
{
	if (funPtr != nullPtr)
	{
		
		if (u8_a_intNumber == INT_0)
		{
			EXTINT_0_callBack = funPtr;
		}
		else if (u8_a_intNumber == INT_1)
		{
			EXTINT_1_callBack = funPtr;
		}
		else if (u8_a_intNumber == INT_2)
		{
			EXTINT_2_callBack = funPtr;
		}
	}
}


ISR(EXT_INT_0)
{
	if (EXTINT_0_callBack != nullPtr)
	{
		EXTINT_0_callBack();
	}
}

ISR(EXT_INT_1)
{
	if (EXTINT_1_callBack != nullPtr)
	{
		EXTINT_1_callBack();
	}
}

ISR(EXT_INT_2)
{
	if (EXTINT_2_callBack != nullPtr)
	{
		EXTINT_2_callBack();
	}
}