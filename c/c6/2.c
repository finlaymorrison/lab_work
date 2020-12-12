#include <util/delay.h>
#include <avr/io.h>

void click()
{
	//Rapidly turn on pin 0 of port A and off again to make a click sound.
	PORTA |= _BV(0);
	_delay_ms(2);
	PORTA &= ~_BV(0);
}

void delay_var(uint16_t num)
{
    for (int i = 0; i < num; ++i)
    {
        _delay_ms(1);
    }
}

int simulate_roulette_wheel(uint8_t num, uint8_t speed, const uint8_t* digits, uint8_t dir)
{
    if (dir == 0) dir = -1;
    while (speed > 0)
    {
        delay_var(2000 / speed);
        click();
        PORTA = digits[num];
        num += dir;
        if (num < 0)
        {
            num = 9;
        }
        num = num % 10;
        --speed;
    }
    return num;
}

int main(void)
{
	DDRA = 0xff;
	DDRC &= ~_BV(1);
	DDRC &= ~_BV(0);
	PORTC |= _BV(1);
	PORTC |= _BV(0);
	const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};
    int pos = 0;
	while (1)
	{
        uint32_t time = 0;
        int8_t clicks = 0;
        uint8_t last_a = 1;
        uint8_t last_b = 1;
        while (clicks < 3 && clicks > -3)
        {
            uint8_t current_a = PINC & _BV(1);
            uint8_t current_b = PINC & _BV(0);
            if (current_b && !last_b && !current_a)
		    {
			    --pos;
                --clicks;
			    click();
		    }
		    if (current_a && !last_a && !current_b)
		    {   
			    ++pos;
                ++clicks;
			    click();
		    }
            pos = pos % 10;
            PORTA = segments[pos];
            ++time;
            last_a = current_a;
            last_b = current_b;
        }
        pos = simulate_roulette_wheel(pos, 1000000000 / time, segments, clicks > 0);
	}
}