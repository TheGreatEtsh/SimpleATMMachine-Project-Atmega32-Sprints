/*
 * buzzer.h
 *
 * Created: 4/18/2023 5:39:19 AM
 *  Author: Ahmed Hesham
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../MCAL/dio/dio.h"

#define NUMBER_OF_BUZZERS	1
#define	BUZZER_0			0


typedef struct buzzer {
	u8 portNumber;
	u8 pinNumber;
	} st_buzzer_t;

typedef enum buzzerError {
	BUZZER_OK,
	WRONG_BUZZER
	} en_buzzerError_t;

en_buzzerError_t	BUZZER_init		(u8 u8_a_buzzerNumber);
en_buzzerError_t	BUZZER_on		(u8 u8_a_buzzerNumber);
en_buzzerError_t	BUZZER_off		(u8 u8_a_buzzerNumber);




#endif /* BUZZER_H_ */