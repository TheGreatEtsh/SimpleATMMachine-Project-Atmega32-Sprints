/*
 * extint.h
 *
 * Created: 4/5/2023 4:41:05 PM
 *  Author: Ahmed Hesham
 */ 


#ifndef EXTINT_H_
#define EXTINT_H_

#include "../registers.h"
#include "../../SERVICE/bit_math.h"
#include "../interrupts.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/****************************************_INTERRUPT_USED_***************************************/
#define INT_0									0
#define INT_1									1
#define INT_2									2

/*******************************************_SENSE_TYPES_***************************************/
#define LOW_LEVEL								1
#define ANY_CHANGE								2
#define FALLING_EDGE							3
#define RISING_EDGE								4

/******************************************_CONFIGURATIONS_***************************************/
/****************************************_SENSE_CONTROL_MODE_***************************************/
/*
 *	TO CHOOSE SENSE CONTROL MODE FOR INT0
 *	OPTION 1	->		LOW_LEVEL
 *	OPTION 2	->		ANY_CHANGE
 *	OPTION 3	->		FALLING_EDGE
 *	OPTION 4	->		RISING_EDGE	
 */

#define SENSE_CONTROL_0		RISING_EDGE

/*
 *	TO CHOOSE SENSE CONTROL MODE FOR INT1
 *	OPTION 1	->		LOW_LEVEL
 *	OPTION 2	->		ANY_CHANGE
 *	OPTION 3	->		FALLING_EDGE
 *	OPTION 4	->		RISING_EDGE	
 */

#define SENSE_CONTROL_1		RISING_EDGE

/*
 *	TO CHOOSE SENSE CONTROL MODE FOR INT2
 *	OPTION 1	->		FALLING_EDGE
 *	OPTION 2	->		RISING_EDGE	
 */

#define SENSE_CONTROL_2		RISING_EDGE

/**********************************************************************************************************************
 *  GLOBAL TYPEDEFS DATA TYPES
 *********************************************************************************************************************/
typedef enum extintError{
	EXTINT_OK,
	WRONG_INT_NUMBER
	}en_extintError_t; 

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/***************************************_PROTOTYPES_***************************************/

/*
 *	CHOOSE EXTERNAL INTERRUPT 
 *	OPTION 1	->		INT_0
 *	OPTION 2	->		INT_1
 *	OPTION 3	->		INT_2
 */
en_extintError_t EXTINT_init (u8 u8_a_intNumber);

void EXTINT_setCallBackInt (u8 u8_a_intNumber, void (*funPtr) (void));




#endif /* EXTINT_H_ */