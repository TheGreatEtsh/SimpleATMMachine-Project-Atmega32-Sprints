/*
 * Button.h
 *
 * Created: 4/3/2023 5:53:31 PM
 *  Author: Ahmed Hesham
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include "../../MCAL/dio/dio.h"

#define BUTTON_1_PORT	PORT_B
#define BUTTON_1_Pin	2

typedef enum buttonErrors{
	BUTTON_OK,
	WRONG_BUTTON_PORT,
	WRONG_BUTTON_PIN
}en_buttonError_t;

en_buttonError_t BUTTON_init(u8 u8_a_buttonPort, u8 u8_a_buttonPin);

en_buttonError_t BUTTON_read(u8 u8_a_buttonPort, u8 u8_a_buttonPin, u8 *u8_a_buttonState);


#endif /* BUTTON_H_ */