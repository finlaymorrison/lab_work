/* Set up the UART0 interface and set stdout and stdin to communicate through the UART0 interface. */
#include "debug.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define AVR_PIN_HIGH_VOLTAGE 3.3f
#define THRESHOLD_VOLTAGE 0.5f

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_BIT PB7

void init_adc()
{
	/* Set reference to AVCC */
	ADMUX |= _BV(REFS0);
    /* Set prescaler to 2^6 = 64. */
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
    /* Enable ADC. */
    ADCSRA |= _BV(ADEN);
}

void init_heartbeat_timer()
{
	TCCR1B |= _BV(CS12) | _BV(CS10); /* Timer 1 Clock speed set to F_CPU / 1024 */
	/* 11720Hz, 11.72 ticks / millisecond */
}

uint16_t read_adc(void)
{
	/* Setting the start conversion bit on ADCSRA. */
    ADCSRA |= _BV(ADSC);
    /* Loop until the ADSC bit has been cleared on the ADCSRA register. */
    loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADC; /* Result of conversion */
}

void channel_adc(uint8_t n)
{
	/* Setting the last 4 bits of the ADMUX register to be the value
	 * of the channel that is specified in the parameter n. */
	ADMUX = (0xF0 & ADMUX) | n;
}

void reset_heartbeat_timer()
{
	TCNT1 = 0; /* Resetting the count */
}

uint16_t get_heartbeat_timer()
{
	return TCNT1; /* Current count of TIMER1 */
}

uint16_t ticks_to_bpm(uint16_t ticks)
{
	/* 60 seconds per minute, timer is running at 11720Hz */
	uint16_t bpm = (11720L * 60L) / ticks;
	return bpm;
}

void init_led_timer()
{
	TCCR0B |= _BV(WGM01); /* Enable CTC mode */
	TCCR0B &= ~(_BV(CS02) | _BV(CS01) | _BV(CS00)); /* Stop clock */
	TIMSK0 |= _BV(OCIE0A); /* Enable output compare interrupt */
	OCR0A = 234; /* Fills up at a rate of 50Hz, 5 fills up will be 100mz */
}

volatile uint8_t fills;

/* Interrupt for when TIMER0 reaches its OCR value */
ISR(TIMER0_COMPA_vect)
{
	++fills;
	/* If timer has filled up 5 times, 100ms has passed */
	if (fills > 4)
	{
		LED_PORT &= ~_BV(LED_BIT);
		TCCR0B &= ~(_BV(CS02) | _BV(CS01) | _BV(CS00)); /* Stop clock */
	}
}

/* Flashes the led at LED_BIT for 100ms */
void flash_led()
{
	TCNT0 = 0; /* Emptying the timer */
	fills = 0; /* Resetting fill count */
	LED_PORT |= _BV(LED_BIT); /* Turning on pulse LED */
	TCCR0B |= _BV(CS02) | _BV(CS00); /* Clock at F_CPU / 1024 = 11720Hz. */
}

int main(void)
{
	init_debug_uart0();
	init_adc();
	init_heartbeat_timer();
	init_led_timer();
	
	sei(); /* Enable global interrupts */

	LED_DDR |= _BV(LED_BIT);

	channel_adc(PA0);

	DDRB |= _BV(PB7);

	uint16_t thresold_value = (uint16_t)(1023 * THRESHOLD_VOLTAGE / AVR_PIN_HIGH_VOLTAGE);

	uint8_t above_threshold = 0;

	while (1) 
	{
		/* Reading the current value from the ADC */
		uint16_t result = read_adc();

		if (result > thresold_value)
		{
			/* If timer has just transitioned from below
			 * to above the threshold value */
			if (!above_threshold)
			{
				/* Getting the ticks since last pulse */
				uint16_t ticks = get_heartbeat_timer();
				/* Converting tick count to BPM */
				uint16_t bpm = ticks_to_bpm(ticks);
				/* Printing BPM through UART */
				printf("%d BPM\n", bpm);
				
				/* Briefly flash the LED at PB7 */
				flash_led();

				/* Resetting the timer for the next pulse */
				reset_heartbeat_timer();

				above_threshold = 1;
			}
		}
		else
		{
			above_threshold = 0;
		}
	}
}