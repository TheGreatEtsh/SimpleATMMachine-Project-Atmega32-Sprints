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




void APP_init (void);
void APP_superLoop (void);
void stillPressed (void);
void APP_buttonTest(void);



#endif /* APP_H_ */