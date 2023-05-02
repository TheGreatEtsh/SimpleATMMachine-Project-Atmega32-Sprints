/*
 * app.h
 *
 * Created: 5/1/2023 3:00:24 PM
 *  Author: Ahmed Hesham
 */ 

#ifndef APP_H_
#define APP_H_
<<<<<<< HEAD
#include "../MCAL/spi/spi.h"
#include "../ECUAL/esp8266/esp8266.h"
=======
#include "../MCAL/uart/uart.h"

#include "../MCAL/i2c/i2c.h" 
#include "../ECUAL/lcd/LCD_Interface.h"
>>>>>>> dbd66c57a5decbde3bf3168774f67f51c9bfbe86

void app_init (void);
 void I2C_TEST (void);


#endif /* APP_H_ */