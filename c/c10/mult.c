/*
 * Project: c10
 * File: c10/mult.c
 * -----
 * File Created: Sunday, 24th January 2021 11:10:01 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:36:07 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/io.h>

#define INT_PORT PORTD

#define SUCCESS 0

void init_adc()
{
	ADMUX |= _BV(REFS0); /* Set reference to AVCC */
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1); /* Set prescaler to 2^6 = 64. */
    ADCSRA |= _BV(ADEN); /* Enable ADC. */
	ADCSRA |= _BV(ADIE); /* Enable ADC Interrupt */
	ADCSRA |= _BV(ADATE); /* Enable auto-triggering */
    ADCSRB |= _BV(ADTS1) | _BV(ADTS0); /* TIMER 0 compare trigger source */
}

void init_adc_timer()
{
	TCCR0A |= _BV(WGM01); /* Enable CTC mode */
    TCCR0B |= _BV(CS02) | _BV(CS00); /* Clock TIMER0 at F_CPU / 1024 */
	OCR0A = 0; /* Start timer at 11720 Hz */
}

void init_int0()
{
    EIMSK |= _BV(INT0); /* Enable INT0 interrupt */
    EICRA |= _BV(ISC01); /* Trigger interrupt on falling edge */
}

void init_int1()
{
    EIMSK |= _BV(INT1); /* Enable INT1 interrupt */
    EICRA |= _BV(ISC11); /* Trigger interrupt on falling edge */
}

/* ADC conversion complete interrupt */
ISR(ADC_vect)
{
    TIFR0 |= _BV(OCF0A); /* Resetting interrupt since TIMER0 ISR is not entered */
	PORTB ^= _BV(PB7); /* Flip PB7 */
}

/* Interrupt on PD2 */
ISR(INT0_vect)
{
    /* Increase value of OCR0A, reducing the frequency */
    if(OCR0A < 255) OCR0A = OCR0A + 1;
}

/* Interrupt on PD3 */
ISR(INT1_vect)
{
    /* Reduce value of OCR0A, increasing the frequency */
    if (OCR0A > 0) OCR0A = OCR0A - 1;
}

int main()
{
    /* Enable pull up resistors for interrupt pins */
    INT_PORT |= _BV(PD2) | _BV(PD3);

    /* Set PB7 as an output */
    DDRB |= _BV(PB7);

    init_adc();
    init_adc_timer();
    init_int0();
    init_int1();

    sei(); /* Enable global interrupts */

    while(1);

    return SUCCESS;
}