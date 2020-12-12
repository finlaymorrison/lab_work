/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <inttypes.h>
#include <ctype.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#define UNIT_LENGTH_MS 	200

void LED_on(void)
{
	PORTB |= _BV(PINB7);
	_delay_ms(UNIT_LENGTH_MS);
}

void LED_off(void)
{
	PORTB &= ~_BV(PINB7);
	_delay_ms(UNIT_LENGTH_MS);
}

int main(void)
{
	DDRB |= _BV(PINB7);
	float pi = 0.0f;
	LED_off();
	for(int i = 1; i < 1000; ++i)
	{
		pi += 1.0f/(i * i);
	}
	pi = sqrt(pi * 6);
	if (pi > 3.14 && pi < 3.15)
	{
		LED_on();
	}
}



