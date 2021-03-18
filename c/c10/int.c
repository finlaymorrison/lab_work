/*
 * Project: c10
 * File: c10/int.c
 * -----
 * File Created: Sunday, 24th January 2021 11:10:01 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:36:05 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/io.h>

#define NUM_DDR DDRC
#define NUM_PORT PORTC

#define INT_PORT PORTD

#define SUCCESS 0

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

volatile uint8_t num;

/* Interrupt on PD2 */
ISR(INT0_vect)
{
    if (NUM_PORT > 0) NUM_PORT = NUM_PORT - 1;
}

/* Interrupt on PD3 */
ISR(INT1_vect)
{
    if(NUM_PORT < 255) NUM_PORT = NUM_PORT + 1;
}

int main()
{
    /* Disabling the JTAG interface in order to use PC2-PC5.
     * Need to set the JTD bit in the MCUCR register twice in
     * the space of 4 clock cycles. */
    MCUCR |= _BV(JTD);
    MCUCR |= _BV(JTD);

    num = 0;
    NUM_DDR = 0xFF;
    NUM_PORT = 0;

    /* Setting interrupts as inputs */
    INT_PORT |= _BV(PD2) | _BV(PD3);

    init_int0();
    init_int1();

    sei(); /* Enable global interrupts */

    while(1);

    return SUCCESS;
}