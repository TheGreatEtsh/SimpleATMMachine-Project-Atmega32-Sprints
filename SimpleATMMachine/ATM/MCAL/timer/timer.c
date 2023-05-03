/*
 * timer.c
 *
 * Created: 4/5/2023 12:38:08 AM
 *  Author: Ahmed Hesham
 */ 

#include "timer.h"

u32 u32_g_timer0NumberOfOVFs	=	0;

u32 u32_g_timer0NumberOfCTCs	=	0;	

u8  u8_g_timer0RemTicks		=	0;

u32 u32_g_timer2NumberOfOVFs	=	0;

u32 u8_g_timer2RemTicks		=	0;

void (*TIMER_0_callBack) (void) = nullPtr;

void (*TIMER_1_callBack) (void) = nullPtr;

void (*TIMER_2_callBack) (void) = nullPtr;

u8 u8_g_normalToPwm			=	0;

u16 u16_g_onTime, u16_g_offTime;


/**

Initializes a timer in the microcontroller based on the specified timer number and operating mode.
u8_a_timerUsed The timer number to initialize (TIMER_0, TIMER_1, or TIMER_2).
en_timerError_t Returns TIMER_OK if initialization was successful, and WRONG_TIMER_USED if the specified timer is not supported.
This function sets the timer mode (OV_TIMER or CTC_TIMER) according to pre-defined constants,
and sets the corresponding timer control registers (TCCR0, TCCR1A/B, TCCR2) accordingly.
If the timer is TIMER_0 or TIMER_2 and the mode is OV_TIMER, the function configures the timer in Normal Mode and enables the overflow interrupt.
If the mode is CTC_TIMER, the function configures the timer in CTC Mode and enables the compare match interrupt.
If the timer is TIMER_1, the function does not perform any initialization and returns immediately with the TIMER_OK status. 
the function enables the global interrupt flag, allowing interrupt requests to be serviced by the microcontroller's interrupt service routine.
*/
en_timerError_t TIMER_init(u8 u8_a_timerUsed)
{
	en_timerError_t en_a_error = TIMER_OK;
	
	if (u8_a_timerUsed == TIMER_0)
	{
		#if			TIMER_0_MODE		==		OV_TIMER
		/*Choosing Normal Mode*/
		CLR_BIT(TCCR0,WGM01); CLR_BIT(TCCR0,WGM00);
		/*Enabling OVF Interrupt 0*/
		SET_BIT(TIMSK,TOIE0);
		
		#elif		TIMER_0_MODE		==		CTC_TIMER
		/*Choosing CTC Mode*/
		SET_BIT(TCCR0,WGM01); CLR_BIT(TCCR0,WGM00);
		/*Enabling CTC Interrupt 0*/
		SET_BIT(TIMSK,OCIE0);
		
		#endif
		/*Enabling Global Interrupt*/
		SET_BIT(SREG, Ibit);

	}
	else if (u8_a_timerUsed == TIMER_1)
	{
	}
	else if (u8_a_timerUsed == TIMER_2)
	{
		#if			TIMER_2_MODE		==		OV_TIMER
		/*Choosing Normal Mode*/
		CLR_BIT(TCCR2,WGM21); CLR_BIT(TCCR2,WGM20);
		/*Enabling OVF Interrupt 0*/
		SET_BIT(TIMSK,TOIE2);
		
		#elif		TIMER_2_MODE		==		CTC_TIMER
		/*Choosing CTC Mode*/
		SET_BIT(TCCR0,WGM21); CLR_BIT(TCCR0,WGM20);
		/*Enabling CTC Interrupt 0*/
		SET_BIT(TIMSK,OCIE2);
		#endif
		
		/*Enabling Global Interrupt*/
		SET_BIT(SREG, Ibit);

	}
	else
	{
		en_a_error = WRONG_TIMER_USED;
	}
	return en_a_error;
}
/*

 This function sets the desired time in milliseconds for a specific timer and mode.
 u8_a_timerUsed Timer to be used (TIMER_0, TIMER_1, or TIMER_2).
 u32_a_desiredTime Desired time in milliseconds.
 en_timerError_t Returns TIMER_OK if successful, or WRONG_TIMER_USED if the selected timer is not available.
*/

en_timerError_t TIMER_setTime(u8 u8_a_timerUsed, u32 u32_a_desiredTime)
{
	en_timerError_t en_a_error = TIMER_OK;
	
	if (u8_a_timerUsed == TIMER_0)
	{
		u32 tickTime = TIMER_0_PRESCALER / XTAL_FREQ;
		u32 numberOfTicks = ((u32_a_desiredTime*1000)/tickTime);
		
		#if		TIMER_0_MODE		==		OV_TIMER
		u32_g_timer0NumberOfOVFs = numberOfTicks / 256;
		u8_g_timer0RemTicks = numberOfTicks % 256;
		if (u8_g_timer0RemTicks)
		{
			TCNT0 = 256 - u8_g_timer0RemTicks;
			u32_g_timer0NumberOfOVFs++;
		}
		
		#elif	TIMER_0_MODE		==		CTC_TIMER
		u8 divisionFactor = 255;
		while(divisionFactor > numberOfTicks)
		{
			divisionFactor--;
		}
		while(numberOfTicks % divisionFactor)
		{
			divisionFactor--;
		}
		u32_g_timer0NumberOfCTCs = numberOfTicks / divisionFactor;
		OCR0 = divisionFactor - 1;
		
		#endif
	}
	else if (u8_a_timerUsed == TIMER_1)
	{
	}
	else if (u8_a_timerUsed == TIMER_2)
	{
	
		u32 tickTime = TIMER_2_PRESCALER / XTAL_FREQ;
		u32 numberOfTicks = ((u32_a_desiredTime*1000)/tickTime);
		
		#if		TIMER_2_MODE		==		OV_TIMER
		u32_g_timer2NumberOfOVFs = numberOfTicks / 256;
		u8_g_timer2RemTicks = numberOfTicks % 256;
		if (u8_g_timer2RemTicks)
		{
			TCNT2 = 256 - u8_g_timer2RemTicks;
			u32_g_timer2NumberOfOVFs++;
		}
		
		#endif
	}
	else
	{
		en_a_error = WRONG_TIMER_USED;
	}
	return en_a_error;
	
}
/**
 *This function sets the duty cycle of a PWM signal for TIMER0.
 *u8_a_timerUsed: The timer to be used. TIMER0 is the only timer supported.
 *u32_a_desiredDutyCycle: The desired duty cycle for the PWM signal (between 0 and 100).
 *en_error: Error code indicating the success or failure of the function.
 */
en_timerError_t TIMER_pwmGenerator(u8 u8_a_timerUsed, u32 u32_a_desiredDutyCycle)
{
	static u8 flag = 0;
	en_timerError_t en_error = TIMER_OK;
	if (u8_a_timerUsed == TIMER_0)	
	{	
		u8_g_normalToPwm = 1;
		u16_g_onTime		= ((u32_a_desiredDutyCycle * 256)/100);
		u16_g_offTime	= 256 - u16_g_onTime;
		DIO_init(PORT_D, 4, OUTPUT);
		DIO_init(PORT_D, 5, OUTPUT);
		if (flag == 0)
		{
			TCNT0 = 256 - u16_g_onTime;
			flag = 1;
		}
		
	}
	else
	{
		en_error = WRONG_TIMER_USED;
	}
	return en_error;
		
}
/**
 * Sets the prescaler value for the specified timer and starts the timer.
 * This function sets the prescaler value for the specified timer and starts the timer. The prescaler value
 * determines the frequency at which the timer increments its value. This function only supports TIMER0 and
 * TIMER2. TIMER1 is not supported. The supported prescaler values are: 1, 8, 64, 256, and 1024.
 * timer  The timer to be started. Must be either TIMER0 or TIMER2.
 * error  Error code indicating the success or failure of the function.               
 */
en_timerError_t TIMER_start(u8 u8_a_timerUsed)
{
	en_timerError_t en_a_error = TIMER_OK;
	
	if (u8_a_timerUsed == TIMER_0)
	{
		#if		TIMER_0_PRESCALER == PRESCLNG_1
		CLR_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	SET_BIT(TCCR0, CS00);
		
		#elif	TIMER_0_PRESCALER == PRESCLNG_8
		CLR_BIT(TCCR0, CS02);	SET_BIT(TCCR0, CS01);	CLR_BIT(TCCR0, CS00);
		
		#elif	TIMER_0_PRESCALER == PRESCLNG_64
		CLR_BIT(TCCR0, CS02);	SET_BIT(TCCR0, CS01);	SET_BIT(TCCR0, CS00);
		
		#elif	TIMER_0_PRESCALER == PRESCLNG_256
		SET_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	CLR_BIT(TCCR0, CS00);
		
		#elif	TIMER_0_PRESCALER == PRESCLNG_1024
		SET_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	SET_BIT(TCCR0, CS00);
		
		#endif
	}
	else if (u8_a_timerUsed == TIMER_1)
	{
	}
	else if (u8_a_timerUsed == TIMER_2)
	{
		#if			TIMER_2_PRESCALER	==		PRESCLNG_1
		CLR_BIT(TCCR2,CS22); CLR_BIT(TCCR2,CS21);	SET_BIT(TCCR2,CS20);
		#elif		TIMER_2_PRESCALER	==		PRESCLNG_8
		CLR_BIT(TCCR2,CS22); SET_BIT(TCCR2,CS21);	CLR_BIT(TCCR2,CS20);
		#elif		TIMER_2_PRESCALER	==		PRESCLNG_64
		SET_BIT(TCCR2,CS22); CLR_BIT(TCCR2,CS21);	CLR_BIT(TCCR2,CS20);
		#elif		TIMER_2_PRESCALER	==		PRESCLNG_256
		SET_BIT(TCCR2,CS22); SET_BIT(TCCR2,CS21);	CLR_BIT(TCCR2,CS20);
		#elif		TIMER_2_PRESCALER	==		PRESCLNG_1024
		SET_BIT(TCCR2,CS22); SET_BIT(TCCR2,CS21);	SET_BIT(TCCR2,CS20);
		#endif

	}
	else
	{
		en_a_error = WRONG_TIMER_USED;
	}
	return en_a_error;
	
}
/* This function stops a timer according to the selected timer number.
 *u8_a_timerUsed: The timer to be stopped.
 *en_error: Error code indicating the success or failure of the function.
 */
en_timerError_t TIMER_stop(u8 u8_a_timerUsed)
{
	en_timerError_t en_a_error = TIMER_OK;
	
	if (u8_a_timerUsed == TIMER_0)
	{
		if (u8_g_normalToPwm)
		{
			DIO_write(PORT_D,4, LOW);
			DIO_write(PORT_D,5, LOW);
			
		}
		CLR_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	CLR_BIT(TCCR0, CS00);
	}
	else if (u8_a_timerUsed == TIMER_1)
	{
	}
	else if (u8_a_timerUsed == TIMER_2)
	{
		CLR_BIT(TCCR2, CS22);	CLR_BIT(TCCR2, CS21);	CLR_BIT(TCCR2, CS20);
	}
	else
	{
		en_a_error = WRONG_TIMER_USED;
	}
	return en_a_error;
	
}
/*
 *This function sets a function to be called when a timer interrupt occurs.
 *u8_a_timerUsed: The timer to be used.
 *funPtr: Pointer to the function to be called when a timer interrupt occurs.
 *return None.
*/
void TIMER_setCallBack(u8 u8_a_timerUsed, void (*funPtr)(void))
{
	if(funPtr != nullPtr)
	{
		if (u8_a_timerUsed == TIMER_0)
		{
			TIMER_0_callBack = funPtr;
		}
		else if (u8_a_timerUsed == TIMER_1)
		{
			TIMER_1_callBack = funPtr;
		}
		else if (u8_a_timerUsed == TIMER_2)
		{
			TIMER_2_callBack = funPtr;
		}
	}
}

/*
 * Disables the interrupt for the specified timer.
 *
 *  u8_a_timerUsed The timer to stop the interrupt for (TIMER_0, TIMER_1, or TIMER_2).
 *
 *  en_timerError_t Returns TIMER_OK if the operation was successful, or WRONG_TIMER_USED if an invalid timer is specified.
 */
en_timerError_t	TIMER_stopInterrupt(u8 u8_a_timerUsed)
{
	en_timerError_t en_a_error;
	
	if (u8_a_timerUsed == TIMER_0)
	{
		CLR_BIT(TIMSK,TOIE0);
		CLR_BIT(TIMSK,OCIE0);
	}
	else if (u8_a_timerUsed == TIMER_1)
	{
		
	}
	else if (u8_a_timerUsed == TIMER_2)
	{
		CLR_BIT(TIMSK,TOIE2);
		CLR_BIT(TIMSK,OCIE2);
	}
	else
	{
		en_a_error = WRONG_TIMER_USED;
	}
	return en_a_error;
}
/*
 * Enables the interrupt for the specified timer.
 *
 *  u8_a_timerUsed The timer to stop the interrupt for (TIMER_0, TIMER_1, or TIMER_2).
 *
 *  en_timerError_t Returns TIMER_OK if the operation was successful, or WRONG_TIMER_USED if an invalid timer is specified.
 */

en_timerError_t	TIMER_enableInterrupt(u8 u8_a_timerUsed)
{
	en_timerError_t en_a_error;
	
	if (u8_a_timerUsed == TIMER_0)
	{
		#if		TIMER_0_MODE		==		OV_TIMER
		SET_BIT(TIMSK,TOIE0);
		#elif	TIMER_0_MODE		==	CTC_TIMER
		SET_BIT(TIMSK,OCIE0);
		#endif
	}
	else if (u8_a_timerUsed == TIMER_1)
	{
		
	}
	else if (u8_a_timerUsed == TIMER_2)
	{
		#if		TIMER_2_MODE		==		OV_TIMER
		SET_BIT(TIMSK,TOIE2);
		#elif	TIMER_2_MODE		==		CTC_TIMER
		SET_BIT(TIMSK,OCIE2);
		#endif
	}
	else
	{
		en_a_error = WRONG_TIMER_USED;
	}
	return en_a_error;
}
/*
 *Delays the program for the specified time using the specified timer.
 *u8_a_timerUsed The timer to use for the delay (TIMER_0, TIMER_1, or TIMER_2).
 *u32_a_timeInMS The time to delay the program in milliseconds. en_timerError_t Returns TIMER_OK if the operation was successful, or WRONG_TIMER_USED if an invalid timer is specified.
 */
en_timerError_t TIMER_delay(u8 u8_a_timerUsed, u32 u32_a_timeInMS)
{
	en_timerError_t en_a_error;
	
	if (u8_a_timerUsed == TIMER_0)
	{

	}
	else if (u8_a_timerUsed == TIMER_1)
	{
		
	}
	else if (u8_a_timerUsed == TIMER_2)
	{
		TIMER_stopInterrupt(TIMER_2);
		TIMER_start(TIMER_2);
		u32 overflowCounter = 0;
		u32 tickTime = 0;
		u32 numberOfTicks = 0;
		u32 numberOfOverflows = 0;
		u8 numberOfRemTicks	= 0;
		
		
		tickTime = TIMER_2_PRESCALER / XTAL_FREQ;
		numberOfTicks = ((u32_a_timeInMS*1000)/tickTime);
		numberOfOverflows = numberOfTicks / 256;
		numberOfRemTicks	= numberOfTicks % 256;
		
		if (numberOfRemTicks)
		{
			numberOfOverflows++;
			TCNT2 = 256 - numberOfRemTicks;
		}
		else
		{
			TCNT2 = 0;
		}
		while(overflowCounter < numberOfOverflows)		
		{
			while((GET_BIT(TIFR, TOV2)) == 0);
			SET_BIT(TIFR, TOV2);
			overflowCounter++;
		}
		TIMER_stop(TIMER_2);
		TIMER_enableInterrupt(TIMER_2);
		
		
	}
	else
	{
		en_a_error = WRONG_TIMER_USED;
	}
	return en_a_error;
	
}

#if			TIMER_0_MODE		==		OV_TIMER
ISR(TIMER0_OVF)
{
	if (u8_g_normalToPwm == 0	)
	{
		
		static u32 OVFCounter = 0;
		OVFCounter  ++;
		if (OVFCounter  == u32_g_timer0NumberOfOVFs)
		{
			if(TIMER_0_callBack != nullPtr)
			{
				TIMER_0_callBack();
			}
			OVFCounter  =	0;
			TCNT0 = 256 - u8_g_timer0RemTicks;
			
		}
	}
	else
	{
		static u8 u8_gs_generatorState = 0;
		if (u8_gs_generatorState)
		{
			DIO_write(PORT_D,4,LOW);
			DIO_write(PORT_D,5,LOW);
			TCNT0 = 256 - u16_g_offTime;
			if (u16_g_offTime < 256)
			{
				u8_gs_generatorState = 0;
			}	
		}
		else
		{
			DIO_write(PORT_D,4, HIGH);
			DIO_write(PORT_D,5, HIGH);
			TCNT0 = 256 - u16_g_onTime;
			if (u16_g_onTime < 256)
			{
				u8_gs_generatorState = 1;
			}
			
		}
		
	}
}

#elif		TIMER_0_MODE		==		CTC_TIMER
ISR(TIMER0_COMP)
{
	static u32 CTCCounter = 0;
	CTCCounter  ++;
	if (CTCCounter  == u32_g_timer0NumberOfCTCs)
	{
		if(TIMER_0_callBack != nullPtr)
		{
			TIMER_0_callBack();
		}
		CTCCounter  =	0;
	}
}
#endif

ISR(TIMER2_OVF)
{		
		static u32 OVFCounter = 0;
		OVFCounter  ++;
		if (OVFCounter  == u32_g_timer2NumberOfOVFs)
		{
			if(TIMER_2_callBack != nullPtr)
			{
				TIMER_2_callBack();
			}
			OVFCounter  =	0;
			TCNT0 = 256 - u8_g_timer2RemTicks;
			
		}

}