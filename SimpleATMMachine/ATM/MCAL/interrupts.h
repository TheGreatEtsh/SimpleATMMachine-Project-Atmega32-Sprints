/*
 * interrupts.h
 *
 * Created: 4/6/2023 3:53:44 AM
 *  Author: Ahmed Hesham
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/*External Interrupt Request 0*/
#define EXT_INT_0					__vector_1

/*External Interrupt Request 1*/
#define EXT_INT_1					__vector_2

/*External Interrupt Request 2*/
#define EXT_INT_2					__vector_3

/*Timer/Counter2 Compare Match*/
#define TIMER2_COMP					__vector_4

/*Timer/Counter2 Overflow*/
#define TIMER2_OVF					__vector_5

/*Timer/Counter1 Capture Event*/
#define TIMER1_CAPT					__vector_6

/*Timer/Counter1 Compare Match A*/
#define TIMER1_COMPA				__vector_7

/*Timer/Counter1 Compare Match B*/
#define TIMER1_COMPB				__vector_8

/*Timer/Counter1 Overflow*/
#define TIMER1_OVF					__vector_9

/*Timer/Counter0 Compare Match*/
#define TIMER0_COMP					__vector_10

/*Timer/Counter0 Overflow*/
#define TIMER0_OVF					__vector_11

/*Serial Transfer Complete*/
#define SPI_STC						__vector_12

/*USART, Rx Complete*/
#define USART_RXC					__vector_13

/*USART, Data Register Empty*/
#define USART_UDRE					__vector_14

/*USART, Tx Complete*/
#define USART_TXC					__vector_15

/*ADC Conversion Complete*/
#define ADC							__vector_16

/*EEPROM Ready*/
#define EE_RDY						__vector_17

/*Analog Comparator*/
#define ANA_COMP					__vector_18

/*Two-wire Serial Interface*/
#define TWI							__vector_19

/*Storage Program Memory Ready*/
#define SPM_READY					__vector_20


#define ISR(INT_VECT)	void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)










#endif /* INTERRUPTS_H_ */