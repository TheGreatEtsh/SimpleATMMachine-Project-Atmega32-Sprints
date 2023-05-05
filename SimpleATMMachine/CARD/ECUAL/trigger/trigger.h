/*
 * trigger.h
 *
 * Created: 5/1/2023 2:59:51 PM
 *  Author: Ahmed Hesham
 */ 


#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "../../MCAL/dio/dio.h"
#include "../../MCAL/timer/timer.h"
#define TRIGGER_PORT				PORT_B 
#define TRIGGER_PIN					0


void TRIGGER_init(void);
void TRIGGER_triggerMCU(void);


#endif /* TRIGGER_H_ */