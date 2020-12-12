/* Set up the UART0 interface and set stdout and stdin to communicate through the UART0 interface. */
#include "debug.h"

#include <avr/io.h>
#include <util/delay.h>

void init_adc()
{
    /* Set prescaler to 2^6 = 64. */
    ADCSRA = 0;
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

#define AVR_PIN_HIGH_VOLTAGE 3.3f

int main(void)
{
	init_debug_uart0();
	init_adc();
	
	while (1) 
	{
		/* Reading the current value from the ADC */
		uint16_t result = read_adc();
		/* Working out the voltage from the result of the ADC. */
		double voltage = (result / 1023.0) * AVR_PIN_HIGH_VOLTAGE;

		/* Printing the value of the ADC through UART. */
		printf("%4d : %6.5fV\n", result, voltage);

		/* Waiting 1 second. */
		//_delay_ms(100);
	}
}