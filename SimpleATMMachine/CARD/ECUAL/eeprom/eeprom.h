/*
 * eeprom.h
 *
 * Created: 5/1/2023 11:00:20 PM
 *  Author: atef
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "i2c.h"
void eeprom_init(void);
en_I2CError_t eeprom_start(void);
en_I2CError_t eeprom_s_address_write(u8 address);
en_I2CError_t eeprom_s_address_read(u8 address);
en_I2CError_t eeprom_write(u8 *data);
en_I2CError_t eeprom_readWACK(u8 *data);
en_I2CError_t eeprom_readWNACK(u8 *data);
void eeprom_stop();
void eeprom_WriteByte(u8 *data ,u8 PageAddress,u8 ByteAddress );
void eeprom_ReadByte (u8 *data ,u8 PageAddress,u8 ByteAddress ); 

#endif /* EEPROM_H_ */