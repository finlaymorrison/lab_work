#include <util/delay.h>

#include <avr/io.h>

#define SUCCESS 0

int main(void)
{
    init_cs_timer();

    DDRC |= 0xFF;

    while(1)
    {
        PORTC = 0x01;
        _delay_ms(50);
        PORTC = 0x00;
        _delay_ms(50);
    }
    return SUCCESS;
}