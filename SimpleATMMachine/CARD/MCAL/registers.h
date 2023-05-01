/*
 * Registers.h
 *
 * Created: 4/3/2023 4:06:53 PM
 * Author : Ahmed Hesham
 * email  : ahmedhesham606@ilcoud.com
 */ 
#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "../SERVICE/standard_types.h"


typedef enum{
	bit0,
	bit1,
	bit2,
	bit3,
	bit4,
	bit5,
	bit6,
	bit7
	}en_bitNumber_t;
	
	
	/************************************************************************/
	/*							SPI_REGISTERS								*/
	/************************************************************************/
	#define SPCR		(*((volatile u8*)(0x2D)))
	#define SPIE		bit7
	#define	SPE         bit6
	#define DORD	    bit5
	#define MSTR	    bit4
	#define CPOL		bit3
	#define CPHA		bit2
	#define SPR1		bit1
	#define SPR0		bit0

	#define SPSR		(*((volatile u8*)(0x2E)))

	#define SPIF		bit7
	#define WCOL		bit6
	#define SPI2X		bit0

	#define SPDR		(*((volatile u8*)(0x2F)))


	/*----------------------------------------------------------------*/	/* TWI stands for "Two Wire Interface" or "TWI Was I2C(tm)" */	#define TWBR    (*(volatile unsigned short*)0x20)	#define TWSR    (*(volatile unsigned short*)0x21)	#define TWAR    (*(volatile unsigned short*)0x22)	#define TWDR    (*(volatile unsigned short*)0x23)	#define TWCR    (*(volatile unsigned short*)0x56)
	/************************************************************************/
	/*							UART_REGISTERS								*/
	/************************************************************************/
	#define UDR		(*((volatile u8*)(0x2C)))
	#define UCSRA		(*((volatile u8*)(0x2B)))
	#define RXC		bit7
	#define	TXC	    bit6
	#define UDRE	bit5
	#define FE		bit4
	#define DOR		bit3
	#define PE		bit2
	#define U2X		bit1
	#define MPCM	bit0

	#define UCSRB	(*((volatile u8*)(0x2A)))
	#define RXCIE	bit7
	#define	TXCIE   bit6
	#define UDRIE   bit5
	#define RXEN	bit4
	#define TXEN	bit3
	#define UCSZ2	bit2
	#define RXB8	bit1
	#define TXB8	bit0

	#define UCSRC	(*((volatile u8*)(0x40)))
	#define URSEL	bit7
	#define	UMSEL   bit6
	#define UPM1    bit5
	#define UPM0	bit4
	#define USBS	bit3
	#define UCSZ1	bit2
	#define UCSZ0	bit1
	#define UCPOL	bit0
	

	#define UBRRH	(*((volatile u8*)(0x40)))

	#define UBRRL	(*((volatile u8*)(0x29)))

	
/************************************************************************/
/*							ADC_REGISTERS								*/
/************************************************************************/
#define ADMUX		(*((volatile u8*)(0x27)))		/*ADC Multiplexer Selection Register*/
#define REF1		bit7							/*Reference Selection Bits*/
#define REF0		bit6							/*Reference Selection Bits*/
#define ADLAR		bit5							/*ADC Left Adjust Result*/
#define MUX4		bit4							/*Analog Channel and Gain Selection Bits*/
#define MUX3		bit3							/*Analog Channel and Gain Selection Bits*/
#define MUX2		bit2							/*Analog Channel and Gain Selection Bits*/
#define MUX1		bit1							/*Analog Channel and Gain Selection Bits*/
#define MUX0		bit0							/*Analog Channel and Gain Selection Bits*/

#define ADCSRA		(*((volatile u8*)(0x26)))		/*ADC Control and Status Register A*/
#define ADEN		bit7							/*ADC Enable*/
#define ADSC		bit6							/*ADC Start Conversion*/
#define ADATE		bit5							/*ADC Auto Trigger Enable*/
#define ADIF		bit4							/*ADC Interrupt Flag*/
#define ADIE		bit3							/*ADC Interrupt Enable*/
#define ADPS2		bit2							/*ADC Prescaler Select Bits*/
#define ADPS1		bit1							/*ADC Prescaler Select Bits*/
#define ADPS0		bit0							/*ADC Prescaler Select Bits*/

#define ADCH		(*((volatile u8*)(0x25)))

#define ADCL		(*((volatile u8*)(0x24)))

/************************************************************************/
/*							DIO_REGISTERS								*/
/************************************************************************/
// PORTD registers
#define PIND		(*((volatile u8*)(0x30)))
#define DDRD		(*((volatile u8*)(0x31)))
#define PORTD		(*((volatile u8*)(0x32)))

// PORTC registers
#define PINC		(*((volatile u8*)(0x33)))
#define DDRC		(*((volatile u8*)(0x34)))
#define PORTC		(*((volatile u8*)(0x35)))

// PORTB registers
#define PINB 		(*((volatile u8*)(0x36)))
#define DDRB		(*((volatile u8*)(0x37)))
#define PORTB		(*((volatile u8*)(0x38)))

// PORTA registers
#define	PINA		(*((volatile u8*)0x39))
#define	DDRA		(*((volatile u8*)0x3A))
#define PORTA		(*((volatile u8*)0x3B))


/************************************************************************/
/*							TIMER_REGISTERS								*/
/************************************************************************/

/********************************_TIMER0_REGISTERS_**********************************/
#define TCCR0		(*((volatile u8*)0x53))
#define FOC0		bit7
#define WGM00		bit6
#define COM01		bit5
#define	COM00		bit4
#define WGM01		bit3
#define CS02		bit2
#define	CS01		bit1
#define	CS00		bit0

#define TIMSK		(*((volatile u8*)0x59))			/*Timer/Counter Interrupt Mask Register*/
#define OCIE2		bit7
#define TOIE2		bit6
#define TICIE1		bit5
#define	OCIE1A		bit4
#define OCIE1B		bit3
#define TOIE1		bit2
#define	OCIE0		bit1
#define	TOIE0		bit0

#define TCNT0		(*((volatile u8*)0x52))

#define OCR0		(*((volatile u8*)0x5C))

#define TIFR		(*((volatile u8*)0x58))
#define OCF2		bit7
#define TOV2		bit6
#define ICF1		bit5
#define OCF1A		bit4
#define OCF1B		bit3
#define TOV1		bit2
#define OVF0		bit1
#define TOV0		bit0

/********************************_TIMER1_REGISTERS_**********************************/
#define ICR1		(*((volatile u16*)0x46))
#define ICR1L		(*((volatile u8*)0x46))
#define ICR1H		(*((volatile u8*)0x47))

#define OCR1A		(*((volatile u16*)0x4A))
#define OCR1AL		(*((volatile u8*)0x4A))
#define OCR1AH		(*((volatile u8*)0x4B))
#define OCR1B		(*((volatile u16*)0x48))
#define OCR1BL		(*((volatile u8*)0x48))
#define OCR1BH 		(*((volatile u8*)0x49))


#define TCNT1		(*((volatile u16*)0x4C))
#define TCNT1L		(*((volatile u8*)0x4C))
#define TCNT1H		(*((volatile u8*)0x4D))

#define TCCR1		(*((volatile u16*)0x4E))
#define TCCR1A		(*((volatile u8*)0x4F))
#define TCCR1B		(*((volatile u8*)0x4E))
#define COM1A1		bit7
#define COM1A0		bit6
#define COM1B1		bit5
#define COM1B0		bit4
#define FOC1A		bit3
#define FOC1B		bit2
#define WGM11		bit1
#define WGM10		bit0
#define ICNC1		bit7
#define ICES1		bit6
#define WGM13		bit4
#define WGM12		bit3
#define CS12		bit2
#define	CS11		bit1
#define	CS10		bit0

/********************************_TIMER2_REGISTERS_**********************************/
#define TCCR2		(*((volatile u8*)0x45))
#define FOC2		bit7
#define WGM20		bit6
#define COM21		bit5
#define	COM20		bit4
#define WGM21		bit3
#define CS22		bit2
#define	CS21		bit1
#define	CS20		bit0

#define TCNT2		(*((volatile u8*)0x44))

#define OCR2		(*((volatile u8*)0x43))

/************************************************************************/
/*							STATUS_REGISTER								*/
/************************************************************************/
#define SREG		(*((volatile u8*)0x5F))			/*AVR Status Register*/
#define Ibit		bit7									/*Global Interrupt Enable*/

/************************************************************************/
/*						EXTERNAL_INTERRUPTS_REGISTERS					*/
/************************************************************************/
#define MCUCR		(*((volatile u8*)0x55))			/*MCU Control Register*/
#define ISC00		bit0
#define ISC01		bit1
#define ISC10		bit2
#define ISC11		bit3

#define MCUCSR		(*((volatile u8*)0x54))			/*MCU Control and Status Register*/
#define ISC2		bit6
#define WDRF		bit3

#define GICR		(*((volatile u8*)0x5B))			/*General Interrupt Control Register*/
#define INT1		bit7
#define INT0		bit6
#define INT2		bit5


#endif // !REGISTERS_H_
