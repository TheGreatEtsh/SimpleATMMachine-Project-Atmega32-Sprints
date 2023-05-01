/*
 * IncFile1.h
 *
 * Created: 4/1/2023 3:55:25 PM
 *  Author: atef
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

 



 
#include "../../MCAL/dio/dio.h"
#include "../../MCAL/timer/timer.h"
 #include "LCD_Interface.h"
 #include "LCD_Cfg.h"
 
 
 
 void LCD_Init(void);
 void LCD_PinsInit ();

void LCD_WriteChar(u8 u8_a_ch);
void LCD_WriteString(u8 *u8_a_str);
void LCD_WriteNumber(i32 i32_a_num);
void LCD_SetCursor(u8 u8_a_line,u8 u8_a_cell);
void LCD_Clear(void);
void LCD_ClearLoc(u8 u8_a_line ,u8 u8_a_cell,u8 u8_a_num);
void LCD_CustomChar(u8 u8_a_loc,u8 *u8_a_pattern);




#endif /* INCFILE1_H_ */