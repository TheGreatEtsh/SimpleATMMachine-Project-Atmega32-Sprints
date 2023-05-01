/*
 * keypad.h
 *
 * Created: 4/18/2023 4:39:20 AM
 *  Author: Ahmed Hesham
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../MCAL/dio/dio.h"
#include "../../MCAL/timer/timer.h"

#define KEYPAD_R0_PORT	PORT_C
#define KEYPAD_R1_PORT	PORT_C
#define KEYPAD_R2_PORT	PORT_C

#define KEYPAD_C0_PORT	PORT_C
#define KEYPAD_C1_PORT	PORT_C
#define KEYPAD_C2_PORT	PORT_C

#define KEYPAD_R0_PIN	2
#define KEYPAD_R1_PIN	3
#define KEYPAD_R2_PIN	4

#define KEYPAD_C0_PIN	5
#define KEYPAD_C1_PIN	6
#define KEYPAD_C2_PIN	7



void KEYPAD_init				(void);
u8	 KEYPAD_read				(void);



#endif /* KEYPAD_H_ */