/*
 * app.h
 *
 * Created: 5/1/2023 3:04:58 PM
 *  Author: Ahmed Hesham
 */ 


#ifndef APP_H_
#define APP_H_

#include "../MCAL/extint/extint.h"
#include "../MCAL/timer/timer.h"
#include "../MCAL/spi/spi.h"
#include "../ECUAL/lcd/LCD_Interface.h"
#include "../ECUAL/keypad/keypad.h"
#include "../ECUAL/buzzer/buzzer.h"
#include "../ECUAL/button/button.h"
#include "server.h"

#define RESETTING_STATE							0
#define BLOCKED_STATE							1
#define PIN_STATE								2
#define RECEIVING_STATE							3
#define VALIDATING_PIN_STATE					4
#define ALARM_STATE								5
#define WITHDRAWL_STATE							6
#define CHECKING_STATE							7
#define PRINTING_BALANCE_STATE					8
#define EJECTING_CARD_STATE						9

void APP_init (void);
void APP_superLoop (void);
void stillPressed (void);
void APP_buttonTest(void);
void atmTriggered(void);
void APP_lcdTEST(void);
void APP_spiSlaveTest(void);
#endif /* APP_H_ */