/*
 * Project: c10
 * File: c10/prep.c
 * -----
 * File Created: Sunday, 24th January 2021 11:10:01 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:36:09 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(ADC_vect)
{
    /* Code to run in interrupt */
}

void init_adc_comp_conv_int()
{
    ADCSRA |= _BV(ADIF); /* Enabling the interrupt flag on the ADC */
}

int main(void)
{
    sei();

    /* INT0 */
    EIMSK |= _BV(INT1); /* Enable INT0 interrupt pin */
    EICRA |= _BV(ISC10) | _BV(ISC11); /* Trigger INT0 on rising edge */

    /* PCINT19, Trigger on any edge */
    PCICR |= _BV(PCIE2); /* Enable port C interrupt bit */
    PCMSK2 |= _BV(PCINT19); /* Masking interrupt for PCINT19/PC3 */

    TIMSK1 |= _BV(OCIE1A); /* TIMER/COUNTER 1 Output compare A */
}