/* Set up the UART0 interface and set stdout and stdin to communicate through the UART0 interface. */
#include "debug.h"

#include <avr/io.h>
#include <util/delay.h>

void init_adc()
{
	/* Set reference to AVCC */
	ADMUX |= _BV(REFS0);
    /* Set prescaler to 2^6 = 64. */
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
    /* Enable ADC. */
    ADCSRA |= _BV(ADEN);
}

uint16_t read_adc(void)
{
	/* Setting the start conversion bit on ADCSRA. */
    ADCSRA |= _BV(ADSC);
    /* Loop until the ADSC bit has been cleared on the ADCSRA register. */
    loop_until_bit_is_clear(ADCSRA, ADSC);
    /* Returning result stored in the ADC register. */
	return ADC;
}

void channel_adc(uint8_t n)
{
	/* Setting the last 4 bits of the ADMUX register to be the value
	 * of the channel that is specified in the parameter n. */
	ADMUX &= 0xF0 | n;
}

#define AVR_PIN_HIGH_VOLTAGE 3.3f

int main(void)
{
	init_debug_uart0();
	init_adc();
	
	channel_adc(0);

	DDRB |= _BV(PB7);

	while (1) 
	{
		/* Reading the current value from the ADC */
		uint16_t result = read_adc();

		/* 880 corresponds to 2.84V on the ADC */
		if (result < 880)
		{
			PORTB |= _BV(PB7);
		}
		else
		{
			PORTB &= ~_BV(PB7);
		}
	}
}