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