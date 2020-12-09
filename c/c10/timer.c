#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#define SEVENSEG_PORT PORTA
#define SEVENSEG_DDR DDRA

#define SUCCSESS 0

void init_seven_seg_timer()
{
	TCCR1B |= _BV(CS12); /* Clock TIMER1 at F_CPU / 256 */
	TIMSK1 |= _BV(OCIE1A); /* Enable output compare interrupt A */
	TCCR1B |= _BV(WGM12); /* Enable CTC mode */
	OCR1A = 46875; /* Fills up at a rate of 1Hz */
}

/* Seven segment display segment values */
const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};

/* Current number on seven segment display */
volatile uint8_t count;

/* Interrupt for when TIMER1 reaches its OCRA value */
ISR(TIMER1_COMPA_vect)
{
	/* Incrementing the value on the seven segment display */
	SEVENSEG_PORT = segments[count];

	/* Increment count and bound in the range 0-9 */
	++count;
	if (count > 9) count = 0;
}

int main(void)
{
	/* Setting the seven segment pins as outputs */
	SEVENSEG_DDR = 0xff;
	/* Initialising display to 0 */
	count = 0;
	SEVENSEG_PORT = segments[count];

	/* Initializing timer that updates the seven segment display */
	init_seven_seg_timer();

	sei(); /* Enable global interrupts */

	while (1);
    
    return SUCCSESS;
}