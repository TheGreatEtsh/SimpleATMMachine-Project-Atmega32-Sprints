/*
 * test-planet.c
 *
 * Created: 4/13/2023 6:41:03 AM
 * Author : atef
 */ 
#define F_CPU 1000000
#include <util/delay.h>
#include "app.h"


void eeprom_test (void);



int main(void)
{  LCD_PinsInit ();
	LCD_Init();
	eeprom_test();
	return 0;
}
void eeprom_test()
{
	u8 val = 0;
	
	DDRD  = 0xFF;
	PORTD = 0x00;
	DDRB  = 0xFF;
	PORTB = 0x00;
	    LCD_SetCursor(0,0);
	    LCD_WriteString("befor ee : ");
	    LCD_WriteNumber(val);*/
	 Init EEPROM */
	eeprom_init();
  
	EEPROM_writeByte(0x0311, 0x07); /* Write  in the external EEPROM */
	_delay_ms(10);
	EEPROM_readByte(0x0311, &val);  /* Read from the external EEPROM */
	
	 LCD_SetCursor(1,0);
	 LCD_WriteString("after ee : ");
	 LCD_WriteNumber(val);
	
	while(1)
	{
		PORTD = val; /* out the read value from the external EEPROM */
	}
}
