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
void eeprom_test_string(void);
void eeprom_test_256(void);
void eeprom_test_string_256(void)



int main(void)
{  LCD_PinsInit ();
	LCD_Init();
	eeprom_test_string();
	return 0;
}
void eeprom_test(void)
{
	u8 val = 0;
	
	DDRD  = 0xFF;
	PORTD = 0x00;
	DDRB  = 0xFF;
	PORTB = 0x00;
	    LCD_SetCursor(0,0);
	    LCD_WriteString("befor ee : ");
	    LCD_WriteNumber(val);
	
	eeprom_init();
  
	EEPROM_writeByte(0x0311, 0x05); 
	_delay_ms(10);
	EEPROM_readByte(0x0311, &val);  
	
	 LCD_SetCursor(1,0);
	 LCD_WriteString("after ee : ");
	 LCD_WriteNumber(val);
	
	while(1)
	{
		PORTD = val; 
	}
}

void eeprom_test_string(void)
{
	u8 val = 0;
	u8 string1[10]="atef";
	u8 string2[10];
	
	DDRD  = 0xFF;
	PORTD = 0x00;
	DDRB  = 0xFF;
	PORTB = 0x00;
	LCD_SetCursor(0,0);
	LCD_WriteString(string1);
	//LCD_WriteNumber(val);
	
	eeprom_init();
	
    eeprom_WriteString_256(0x0311,string1);
	_delay_ms(10);
	eeprom_ReadString_256(0x0311,string2);
	
	LCD_SetCursor(1,0);
	LCD_WriteString(string2);
	//LCD_WriteNumber(val);
	
	while(1)
	{
		PORTD = val;
	}
} 
void eeprom_test_256(void)
{
	u8 val = 0;
	
	DDRD  = 0xFF;
	PORTD = 0x00;
	DDRB  = 0xFF;
	PORTB = 0x00;
	LCD_SetCursor(0,0);
	LCD_WriteString("befor ee : ");
	LCD_WriteNumber(val);
	
	eeprom_init();
	
	EEPROM_writeByte(0x0311, 0x07);
	_delay_ms(10);
	EEPROM_readByte(0x0311, &val);
	
	LCD_SetCursor(1,0);
	LCD_WriteString("after ee : ");
	LCD_WriteNumber(val);
	
	while(1)
	{
		PORTD = val;
	}
} 
void eeprom_test_string_256(void)
{
	u8 val = 0;
	u8 string1[10]="atef";
	u8 string2[10];
	
	DDRD  = 0xFF;
	PORTD = 0x00;
	DDRB  = 0xFF;
	PORTB = 0x00;
	LCD_SetCursor(0,0);
	LCD_WriteString(string1);
	//LCD_WriteNumber(val);
	
	eeprom_init();
	
	eeprom_WriteString_256(0x0311,string1);
	_delay_ms(10);
	eeprom_ReadString_256(0x0311,string2);
	
	LCD_SetCursor(1,0);
	LCD_WriteString(string2);
	//LCD_WriteNumber(val);
	
	while(1)
	{
		PORTD = val;
	}
}