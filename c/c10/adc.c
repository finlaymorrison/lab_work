/*
 * Project: c10
 * File: c10/adc.c
 * -----
 * File Created: Sunday, 24th January 2021 11:10:01 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:36:02 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/io.h>

void init_adc_freerun()
{
	ADMUX |= _BV(REFS0); /* Set reference to AVCC */
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1); /* Set prescaler to 2^6 = 64. */
    ADCSRA |= _BV(ADEN); /* Enable ADC. */
	ADCSRA |= _BV(ADIE); /* Enable ADC Interrupt */
	ADCSRA |= _BV(ADATE); /* Enable auto-triggering */
	ADCSRA |= _BV(ADSC); /* Start first conversion */
}

ISR(ADC_vect)
{
	PORTB ^= _BV(PB7); /* Flip PB7 */
}

int main(void)
{
	sei(); /* Enable global interrupts */

	init_adc_freerun();

	DDRB |= _BV(PB7);

	while (1);
}