/*
 * app.h
 *
 * Created: 5/1/2023 3:00:24 PM
 *  Author: Ahmed Hesham
 */ 

#ifndef APP_H_
#define APP_H_
#include "../MCAL/uart/uart.h"

#include "../MCAL/i2c/i2c.h" 
#include "../ECUAL/lcd/LCD_Interface.h"

void app_init (void);
 void I2C_TEST (void);


#endif /* APP_H_ */