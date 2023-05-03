/*
 * eeprom.h
 *
 * Created: 5/1/2023 11:00:20 PM
 *  Author: atef
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "i2c.h"
#include "lcd.h"
void eeprom_init(void);
void eeprom_WriteByte(u8 *data ,u16 u16_addr);
void eeprom_ReadByte (u8 *data ,u16 u16_addr ); 

#endif /* EEPROM_H_ */