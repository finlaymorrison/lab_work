/*
 * Project: c7
 * File: c7/main.c
 * -----
 * File Created: Sunday, 24th January 2021 11:10:01 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:34:26 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include "spi.h"
#include "digitalPot.h"

#include <util/delay.h>

int main(void)
{
	/* Initializing the digital potentiometer */
	init_pot();

	uint8_t num = 0;

	while (1)
	{
		/* Looping back around once it gets to 255 */
		if (num == 255)
		{
			setXpot(0x0);
			num = 0;
		}
		else
		incXpot();
		++num;
		_delay_ms(1);
	}
}