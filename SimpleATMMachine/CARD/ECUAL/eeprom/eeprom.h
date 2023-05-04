/*
 * eeprom.h
 *
 * Created: 5/1/2023 11:00:20 PM
 *  Author: atef
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "../../MCAL/i2c/i2c.h"
#include "../../MCAL/timer/timer.h"


void EEPROM_init(void);
/*-------------------------16--------------------------*/
u8 EEPROM_writeByte(u16 u16addr, u8 u8data);
u8 EEPROM_readByte(u16 u16addr, u8 *u8data);
u8 eeprom_WriteString (u16 u16_Saddr, u8 *u8_Pdata);
u8 eeprom_ReadString (u16 u16_Saddr, u8 *u8_Pdata);
/*-------------------------256--------------------------*/
u8 EEPROM_writeByte_256(u16 u16_addr, u8 u8data);
u8 EEPROM_readByte_256(u16 u16addr, u8 *u8data);
u8 EEPROM_writeString_256 (u16 u16_Saddr, u8 *u8_Pdata);
u8 EEPROM_readString_256 (u16 u16_Saddr, u8 *u8_Pdata);

#endif /* EEPROM_H_ */