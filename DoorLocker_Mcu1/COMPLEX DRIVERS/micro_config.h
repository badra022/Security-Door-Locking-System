 /******************************************************************************
 *
 * Module: Lcd
 *
 * File Name: lcd.h
 *
 * Description: lcd header file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/
#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 1000000UL //1MHz Clock frequency
#endif

#ifndef NULL
#define NULL (void *)0
#endif

/*#include <avr/io.h>*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include"string.h"
/*
#define SREG 	(*(volatile uint8 * const)0x5F)
#define SPH 	(*(volatile uint8 * const)0x5E)
#define SPL 	(*(volatile uint8 * const)0x5D)
#define SP 		(*(volatile uint16* const)0x5D)
#define OCR0 	(*(volatile uint8 * const)0x5C)
#define GICR 	(*(volatile uint8 * const)0x5B)
#define GIFR 	(*(volatile uint8 * const)0x5A)
#define TIMSK 	(*(volatile uint8 * const)0x59)
#define TIFR 	(*(volatile uint8 * const)0x58)
#define SPMCR 	(*(volatile uint8 * const)0x57)
#define TWCR 	(*(volatile uint8 * const)0x56)
#define MCUCR 	(*(volatile uint8 * const)0x55)
#define MCUCSR 	(*(volatile uint8 * const)0x54)
#define TCCR0 	(*(volatile uint8 * const)0x53)
#define TCNT0 	(*(volatile uint8 * const)0x52)
#define OSCCAL 	(*(volatile uint8 * const)0x51)
#define OCDR	(*(volatile uint8 * const)0x51)
#define SFIOR 	(*(volatile uint8 * const)0x50)
#define TCCR1A 	(*(volatile uint8 * const)0x4F)
#define TCCR1B 	(*(volatile uint8 * const)0x4E)
#define TCNT1 	(*(volatile uint16* const)0x4C)
#define TCNT1H 	(*(volatile uint8 * const)0x4D)
#define TCNT1L 	(*(volatile uint8 * const)0x4C)
#define OCR1A 	(*(volatile uint16* const)0x4A)
#define OCR1AH 	(*(volatile uint8 * const)0x4B)
#define OCR1AL 	(*(volatile uint8 * const)0x4A)
#define OCR1B 	(*(volatile uint16* const)0x48)
#define OCR1BH 	(*(volatile uint8 * const)0x49)
#define OCR1BL	(*(volatile uint8 * const)0x48)
#define ICR1 	(*(volatile uint8 * const)0x46)
#define ICR1H 	(*(volatile uint8 * const)0x47)
#define ICR1L 	(*(volatile uint8 * const)0x46)
#define TCCR2 	(*(volatile uint8 * const)0x45)
#define TCNT2	(*(volatile uint8 * const)0x44)
#define OCR2	(*(volatile uint8 * const)0x43)
#define ASSR 	(*(volatile uint8 * const)0x42)
#define WDTCR 	(*(volatile uint8 * const)0x41)
#define UBRRH 	(*(volatile uint8 * const)0x40)
#define UCSRC	(*(volatile uint8 * const)0x40)
#define EEARH	(*(volatile uint8 * const)0x3F)
#define EEARL	(*(volatile uint8 * const)0x3E)
#define EEDR	(*(volatile uint8 * const)0x3D)
#define EECR 	(*(volatile uint8 * const)0x3C)
#define PORTA 	(*(volatile uint8 * const)0x3B)
#define DDRA	(*(volatile uint8 * const)0x3A)
#define PINA 	(*(volatile uint8 * const)0x39)
#define PORTB 	(*(volatile uint8 * const)0x38)
#define DDRB	(*(volatile uint8 * const)0x37)
#define PINB 	(*(volatile uint8 * const)0x36)
#define PORTC 	(*(volatile uint8 * const)0x35)
#define DDRC	(*(volatile uint8 * const)0x34)
#define PINC	(*(volatile uint8 * const)0x33)
#define PORTD	(*(volatile uint8 * const)0x32)
#define DDRD	(*(volatile uint8 * const)0x31)
#define PIND	(*(volatile uint8 * const)0x30)
#define SPDR	(*(volatile uint8 * const)0x2F)
#define SPSR	(*(volatile uint8 * const)0x2E)
#define SPCR	(*(volatile uint8 * const)0x2D)
#define UDR		(*(volatile uint8 * const)0x2C)
#define UCSRA	(*(volatile uint8 * const)0x2B)
#define UCSRB	(*(volatile uint8 * const)0x2A)
#define UBRRL	(*(volatile uint8 * const)0x29)
#define ACSR	(*(volatile uint8 * const)0x28)
#define ADMUX	(*(volatile uint8 * const)0x27)
#define ADCSRA	(*(volatile uint8 * const)0x26)
#define ADC		(*(volatile uint16* const)0x24)
#define TWDR	(*(volatile uint8 * const)0x23)
#define TWAR	(*(volatile uint8 * const)0x22)
#define TWSR	(*(volatile uint8 * const)0x21)
#define TWBR	(*(volatile uint8 * const)0x20)
*/

#define GLOBAL_INTERRUPT_ENABLE() SET_BIT(SREG,7)
#endif /* MICRO_CONFIG_H_ */
