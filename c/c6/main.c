#include <util/delay.h>
#include <avr/io.h>

void click()
{
	//Rapidly turn on pin 0 of port A and off again to make a click sound.
	PORTA |= _BV(0);
	_delay_ms(2);
	PORTA &= ~_BV(0);
}

int main(void)
{
	DDRA = 0xff;
	DDRC &= ~_BV(1);
	DDRC &= ~_BV(0);
	PORTC |= _BV(1);
	PORTC |= _BV(0);
	const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};
	int8_t pos = 0;
	uint8_t last_a = 1;
	uint8_t last_b = 1;
	while (1)
	{
		uint8_t current_a = PINC & _BV(1);
		uint8_t current_b = PINC & _BV(0);
		if (current_b && !last_b && !current_a)
		{
			--pos;
			click();
		}
		if (current_a && !last_a && !current_b)
		{
			++pos;
			click();
		}
		if (pos > 9)
		{
			pos = 0;
		}
		if (pos < 0)
		{
			pos = 9;
		}
		last_a = current_a;
		last_b = current_b;
		PORTA = segments[pos];
	}
}