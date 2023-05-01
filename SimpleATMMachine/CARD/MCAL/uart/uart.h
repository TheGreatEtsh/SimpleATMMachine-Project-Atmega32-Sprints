x/*
 * uart.h
 *
 * Created: 5/1/2023 2:58:11 PM
 *  Author: Ahmed Hesham
 */ 


#ifndef UART_H_
#define UART_H_


#include "../dio/dio.h"
#include "../registers.h"
#include "../../SERVICE/bit_math.h"

void UART_Init(void);

void UART_SendChar(u8 data);

u8 UART_GetChar(void);






#endif /* UART_H_ */