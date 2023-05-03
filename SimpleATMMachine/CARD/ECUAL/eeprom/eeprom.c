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
