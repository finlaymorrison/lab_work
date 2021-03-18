/*
 * Project: c11
 * File: c11/main.c
 * -----
 * File Created: Sunday, 24th January 2021 11:10:01 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:36:16 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <util/delay.h>

#include <avr/io.h>

#define SUCCESS 0

int main(void)
{
    init_cs_timer();

    DDRC |= 0xFF;

    while(1)
    {
        PORTC = 0x01;
        _delay_ms(50);
        PORTC = 0x00;
        _delay_ms(50);
    }
    return SUCCESS;
}