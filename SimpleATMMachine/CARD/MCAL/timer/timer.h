/*
 * timer.h
 *
 * Created: 4/5/2023 12:38:41 AM
 *  Author: Ahmed Hesham
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../registers.h"
#include "../../SERVICE/bit_math.h"
#include "../interrupts.h"
#include "../dio/dio.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
// TIMER NUMBERS
#define TIMER_0									0
#define TIMER_1									1
#define TIMER_2									2



// TIMER WAVEFORM TYPES
#define OV_TIMER								0
#define CTC_TIMER								1

// PRESCALER OPTIONS
#define NO_CLK									0
#define PRESCLNG_1								1
#define PRESCLNG_8								8
#define PRESCLNG_64								64
#define PRESCLNG_256							256
#define PRESCLNG_1024							1024
#define XCK_FLNG_EDGE							10
#define XCK_RSNG_EDGE							15

/******************************************_CONFIGURATIONS_***************************************/
/*****************************************_TIMER_MODE_USED_***************************************/

#define TIMER_0_MODE							OV_TIMER
#define TIMER_1_MODE							OV_TIMER
#define TIMER_2_MODE							OV_TIMER
/*****************************************_PRESCALER_USED_***************************************/
#define TIMER_0_PRESCALER						PRESCLNG_256
#define TIMER_1_PRESCALER						PRESCLNG_256
#define TIMER_2_PRESCALER						PRESCLNG_256

/**************************************_CLOCK_FREQUENCY_USED_************************************/
#define XTAL_FREQ								16

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum timerError{
	TIMER_OK,
	WRONG_TIMER_USED,
	WRONG_DESIRED_TIME
	}en_timerError_t;


en_timerError_t TIMER_init(u8 u8_a_timerUsed);
en_timerError_t TIMER_setTime(u8 u8_a_timerUsed, u32 u32_a_desiredTime);
en_timerError_t TIMER_start(u8 u8_a_timerUsed);
en_timerError_t TIMER_stop(u8 u8_a_timerUsed);
en_timerError_t TIMER_pwmGenerator(u8 u8_a_timerUsed, u32 u32_a_desiredDutyCycle);
void			TIMER_setCallBack(u8 u8_a_timerUsed, void (*funPtr)(void));
en_timerError_t	TIMER_stopInterrupt(u8 u8_a_timerUsed);
en_timerError_t TIMER_delay(u8 u8_a_timerUsed, u32 u32_a_timeInMS);
en_timerError_t	TIMER_enableInterrupt(u8 u8_a_timerUsed);




#endif /* TIMER_H_ */