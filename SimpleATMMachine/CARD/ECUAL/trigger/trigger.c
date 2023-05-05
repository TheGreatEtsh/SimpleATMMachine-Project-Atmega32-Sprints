/*
 * trigger.c
 *
 * Created: 5/1/2023 2:59:39 PM
 *  Author: Ahmed Hesham
 */ 

#include "trigger.h"

void TRIGGER_init(void)
{
	DIO_init(TRIGGER_PORT, TRIGGER_PIN, OUTPUT);
}

void TRIGGER_triggerMCU(void)
{
	DIO_write(TRIGGER_PORT, TRIGGER_PIN, HIGH);
	TIMER_delay(TIMER_2, 200);
	DIO_write(TRIGGER_PORT, TRIGGER_PIN, LOW);
}
