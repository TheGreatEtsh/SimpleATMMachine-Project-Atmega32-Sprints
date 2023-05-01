/*
 * eeprom.c
 *
 * Created: 5/1/2023 11:00:07 PM
 *  Author: atef
 */ 
#include "eeprom.h" 


void eeprom_init()
{
	I2C_init();
}
en_I2CError_t eeprom_start()
{
	return I2C_start();
}
en_I2CError_t eeprom_s_address_write(u8 address)
{
	 return I2C_address_select(address,write);
}
en_I2CError_t eeprom_s_address_read(u8 address)
{
	return I2C_address_select(address,read);
}
en_I2CError_t eeprom_write(u8 *data)
{
	return I2C_data_rw(data,write,ACK);
}
en_I2CError_t eeprom_readWACK(u8 *data)
{
	 return I2C_data_rw(data,read,ACK);
}
en_I2CError_t eeprom_eeprom_readWNACK(u8 *data)
{
	return I2C_data_rw(data,read,NACK);
}
void eeprom_stop()
{
	I2C_stop();
} 
en_I2CError_t eeprom_RepeatedStart()
{
	 return I2C_repeated_start();
}

void eeprom_WriteByte(u8 *data ,u8 PageAddress,u8 ByteAddress )
{
		if (eeprom_start()==EVENT_OK)
		{
			if ( eeprom_s_address_write((0x50|PageAddress))==SLA_W_ACK_SENT)
			{       
				if(eeprom_write(ByteAddress)==DATA_WRITE_ACK_SENT)
				{ 
					if(eeprom_write(data)==DATA_WRITE_ACK_SENT)
					{
				
					I2C_stop();
					
					}
				}
			}
		}
	
}
void eeprom_ReadByte (u8 *ee_data ,u8 PageAddress,u8 ByteAddress )
{
			if (eeprom_start()==EVENT_OK)
			{
				if ( eeprom_s_address_write((0x50|PageAddress))==SLA_W_ACK_SENT)
				{
					if(eeprom_write(ByteAddress)==DATA_WRITE_ACK_SENT)
					{
						if(eeprom_write(ee_data)==DATA_WRITE_ACK_SENT)
						{
							if (eeprom_RepeatedStart()==REPEATED_START_NOT_SENT)
							{
								if ( eeprom_s_address_read((0x50|PageAddress))==SLA_R_ACK_SENT)
								{
									if(eeprom_eeprom_readWNACK(ee_data)==DATA_READ_NACK_SENT)
									{
										eeprom_stop();
									}
								}
								
							}
							
							
						}
					}
				}
			}
}
