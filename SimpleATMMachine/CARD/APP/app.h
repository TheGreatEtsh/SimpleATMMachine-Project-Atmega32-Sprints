/*
 * app.h
 *
 * Created: 5/1/2023 3:00:24 PM
 *  Author: Ahmed Hesham
 */ 

#ifndef APP_H_
#define APP_H_

#include "../MCAL/timer/timer.h"
#include "../MCAL/uart/uart.h"
#include "../MCAL/spi/spi.h"
#include "../ECUAL/eeprom/eeprom.h"
#include "../ECUAL/trigger/trigger.h"
#include "../ECUAL/lcd/LCD_Interface.h"

#define PAN_ADDRESS					0x10
#define PIN_ADDRESS					0x30

#define	USER_MODE					1


#define	PROGRAMMING_MODE			2
#define PRO_INITIAL_STATE			0
#define PRO_SAVING_PAN				1
#define PRO_RECEIVING_PIN			2


#define EEPROM_EMPTY				0
#define EEPROM_NOT_EMPTY			1

void APP_init (void);
void APP_superLoop (void);
u8 APP_checkEEPROM(void);
void APP_testingEEPROM (void);
void APP_deleteAll (void);
void I2C_TEST (void);
void APP_testingUART();

#endif /* APP_H_ */