/*
 * eeprom.c
 *
 * Created: 5/1/2023 11:00:07 PM
 *  Author: atef
 */ 
#define F_CPU 1000000
#include <util/delay.h>
#include "eeprom.h" 



void EEPROM_init()
{
	I2C_init();
}
/*-----------------------16-------------------------------*/
u8 EEPROM_writeByte(u16 u16addr, u8 u8data)
{
    /* Send the Start Bit */
    if (I2C_start()==EVENT_OK)
    {
        /* Send the device address, we need to get A8 A9 A10 address bits from the
         * memory location address and R/W=0 (write) */
        if (I2C_address_select((u8)(0xA0 | ((u16addr & 0x0700)>>7)),write)==SLA_W_ACK_SENT)
        {  
            /* Send the required memory location address */
            if (I2C_data_rw((u8)(u16addr),write,ACK)==DATA_WRITE_ACK_SENT)
            {
                /* write byte to eeprom */
                if (I2C_data_rw(u8data,write,ACK)==DATA_WRITE_ACK_SENT)
                {
                    /* Send the Stop Bit */
                    I2C_stop();
                }
            }
        }
    }
}
u8 EEPROM_readByte(u16 u16addr, u8 *u8data)
{
    /* Send the Start Bit */
    if (I2C_start()==EVENT_OK)
    {
        /* Send the device address, we need to get A8 A9 A10 address bits from the
         * memory location address and R/W=0 (write) */
        if (I2C_address_select((u8)(0xA0 | ((u16addr & 0x0700)>>7)),write)==SLA_W_ACK_SENT)
        {
            /* Send the required memory location address */
            if (I2C_data_rw((u8)(u16addr),write,ACK)==DATA_WRITE_ACK_SENT)
            {
                /* Send the Repeated Start Bit */
                if (I2C_repeated_start()==EVENT_OK)
                {
                    /* Send the device address, we need to get A8 A9 A10 address bits from the
                     * memory location address and R/W=1 (Read) */

                    if (I2C_address_select((u8)(0xA0 | ((u16addr & 0x0700)>>7)),read)==SLA_R_ACK_SENT)
                    {
                        /* Read Byte from Memory without send ACK */

                        if (I2C_data_rw(u8data,read,NACK)==DATA_READ_NACK_SENT)
                        {
                            /* Send the Stop Bit */
                            I2C_stop();

                        }
                    }
                }
            }
        }
    }
}
u8 eeprom_WriteString (u16 u16_Saddr, u8 *u8_Pdata)
{ 
		/*u8 len = 0;
		
		do
		{
			EEPROM_writeByte( u16_Saddr++,u8_Pdata[len]);
			_delay_ms(20);
			
		}
		while(u8_Pdata[len++] != '\0');*/
		
		
				u8 i;
				u16 ee_address=u16_Saddr;
				for (i=0;u8_Pdata[i];i++)
				{
					EEPROM_writeByte(ee_address++,u8_Pdata[i]);
					_delay_ms(20);
				}
				
				EEPROM_writeByte(ee_address,'\0');
				
				
}
u8 eeprom_ReadString (u16 u16_Saddr, u8 *u8_Pdata)
{
			u8 i = 0;
			do
			{
				 EEPROM_readByte(u16_Saddr++,&u8_Pdata[i]);
				_delay_ms(20);
			} 
			while(u8_Pdata[i++] != '\0');
		
				
			
}

/*-----------------------256-------------------------------*/
u8 EEPROM_writeByte_256(u16 u16_addr, u8 u8data)
{
    /* Send the Start Bit */
    if (I2C_start()==EVENT_OK)
    {
        /* Send the device address, we need to get A8 A9 A10 address bits from the
         * memory location address and R/W=0 (write) */
        if (I2C_address_select(0xA0,write)==SLA_W_ACK_SENT)
        {
            /* Send the required memory location address */
            if (I2C_data_rw((u8)((u16_addr >> 8) & 0xFF),write,ACK)==DATA_WRITE_ACK_SENT)
            {
                if (I2C_data_rw((u8)(u16_addr),write,ACK)==DATA_WRITE_ACK_SENT)
                {

                    /* write byte to eeprom */
                    if (I2C_data_rw(u8data,write,ACK)==DATA_WRITE_ACK_SENT)
                    {
                        /* Send the Stop Bit */
                        I2C_stop();
                    }
                }
            }
        }
    }
}
u8 EEPROM_readByte_256(u16 u16_addr, u8 *u8data)
{
    /* Send the Start Bit */
    if (I2C_start()==EVENT_OK)
    {
        /* Send the device address, we need to get A8 A9 A10 address bits from the
         * memory location address and R/W=0 (write) */
        if (I2C_address_select(0xA0,write)==SLA_W_ACK_SENT)
        {
            /* Send the required memory location address */
            if (I2C_data_rw((u8)((u16_addr >> 8) & 0xFF),write,ACK)==DATA_WRITE_ACK_SENT)
            {
                if (I2C_data_rw((u8)(u16_addr),write,ACK)==DATA_WRITE_ACK_SENT)
                {
                    /* Send the Repeated Start Bit */
                    if (I2C_repeated_start()==EVENT_OK)
                    {
                        /* Send the device address, we need to get A8 A9 A10 address bits from the
                         * memory location address and R/W=1 (Read) */

                        if (I2C_address_select(0xA0,read)==SLA_R_ACK_SENT)
                        {
                            /* Read Byte from Memory without send ACK */

                            if (I2C_data_rw(u8data,read,NACK)==DATA_READ_NACK_SENT)
                            {
                                /* Send the Stop Bit */
                                I2C_stop();

                            }
                        }
                    }
                }
            }
        }
    }
}
u8 EEPROM_writeString_256 (u16 u16_Saddr, u8 *u8_Pdata)
{ 
	
	u8 i;
	u16 ee_address=u16_Saddr;
	for (i=0;u8_Pdata[i];i++)
	{
		EEPROM_writeByte_256(ee_address++,u8_Pdata[i]);
		TIMER_delay(TIMER_2,20);
	}
	
	EEPROM_writeByte_256(ee_address,'\0');			
				
}
u8 EEPROM_readString_256 (u16 u16_Saddr, u8 *u8_Pdata)
{
	u8 i = 0;
	do
	{
		EEPROM_readByte_256(u16_Saddr++,&u8_Pdata[i]);
		TIMER_delay(TIMER_2,30);
	} 
	while(u8_Pdata[i++] != '\0');
}
