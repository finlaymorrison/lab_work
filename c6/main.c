#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
	DDRA = 0xff;
	DDRC = 0x00;
	PORTC = 0xff;
	const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};
	uint8_t pos = 0;
	while (1)
	{
		while (!(PINC & _BV(0)));
		++pos;
		pos = pos % 10;
		PORTA = segments[pos];
		while (PINC & _BV(0));
	}
}
