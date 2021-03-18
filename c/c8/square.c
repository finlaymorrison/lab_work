/*
 * Project: c8
 * File: c8/square.c
 * -----
 * File Created: Sunday, 24th January 2021 11:10:01 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:34:45 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

/* Creates a constant square wave tone on PD5 at a frequency defined by FREQ*/

#include <avr/io.h>
#include <util/delay.h>

#define FREQ 262

#define TONE_PRESCALER 8UL


unsigned long tone_clock;   /* set at timer initialisation and used to calculate TOP when setting frequency */ 

void init_tone(void);
void tone(uint16_t frequency);

int main(void) {

    init_tone();
    while (1) 
    {
        tone(FREQ);
    }
}

void init_tone(void)
{
    DDRD |= _BV(PD5); /* Enable output driver for OC1A */
    TCCR1A = _BV(COM1A0) | _BV(WGM10); /* Toggle OC1A on match, frequency(f) correct PWM */
    TCCR1B = _BV(WGM13) | _BV(CS11); /* Varying f with OCR1A, prescaler set to 8 */
    tone_clock = F_CPU / (TONE_PRESCALER * 2);
}

void tone(uint16_t frequency)
{
    /* Frequency is multipled by 2, since the counter flips the output
     * every time, which is half a full wavelength, so the frequency
     * must be multiplied 2 so that this error can be corrected. */
    uint16_t top_val = tone_clock / (frequency * 2);
    OCR1A = top_val;
}