/*
 * Project: c8
 * File: c8/scale.c
 * -----
 * File Created: Sunday, 24th January 2021 11:10:01 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:34:43 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "et_scale.h"

#include <avr/io.h>
#include <util/delay.h>

#define TONE_PRESCALER 8UL


unsigned long tone_clock;

void init_tone(void);
void tone(uint16_t frequency);

int main(void) {

    init_tone();
    while (1) 
    {
        uint16_t i = 0;
        for (; i < ET_SCALE_TOP; ++i)
        {
            tone(et_scale[i]);
            _delay_ms(500);
        }
        for (;i > 0; --i)
        {
            tone(et_scale[i]);
            _delay_ms(500);
        }
    }
}

void init_tone(void)
{
    DDRD |= _BV(PD5);
    TCCR1A = _BV(COM1A0) | _BV(WGM10);
    TCCR1B = _BV(WGM13) | _BV(CS11);
    tone_clock = F_CPU / (TONE_PRESCALER * 2);
}

void tone(uint16_t frequency)
{
    uint16_t top_val = tone_clock / (frequency * 2);
    OCR1A = top_val;
}