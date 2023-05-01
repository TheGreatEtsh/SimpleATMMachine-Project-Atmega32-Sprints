/*
 * dio.h
 *
 * Created: 4/3/2023 4:15:52 PM
 *  Author: Ahmed Hesham
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "../registers.h"
#include "../../SERVICE/bit_math.h"

// all internal driver typedefs
// all driver macros
#define PORT_A			'A'
#define PORT_B			'B'
#define PORT_C			'C'
#define PORT_D			'D'

#define INPUT			0
#define OUTPUT			1

#define LOW				0
#define HIGH			1

#define PULLUP_DISABLE	0
#define PULLUP_ENABLE	1


// all driver function prototypes
typedef enum dioError{
	DIO_OK,
	WRONG_PORT_NUMBER,
	WRONG_PIN_NUMBER,
	WRONG_VALUE,
	WRONG_DIRECTION
	}en_dioError_t;

en_dioError_t DIO_init(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 u8_a_direction);	// Initialize dio direction
en_dioError_t DIO_write(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 u8_a_value);		// Write data to dio
en_dioError_t DIO_toggle(u8 u8_a_portNumber, u8 u8_a_pinNumber);						// Toggle dio 
en_dioError_t DIO_read(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 *u8_a_value);		// Read dio
en_dioError_t DIO_pinPullUp(u8 u8_a_portNumber, u8 u8_a_pinNumber, u8 pullUpState);

#endif /* DIO_H_ */