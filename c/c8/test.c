#include <stdint.h>
#include <avr/io.h>

int main(void)
{
    uint8_t num = 0;
    DDRA |= _BV(0); /* Set PA0 to an output */
    DDRC &= _BV(2); /* Set PC2 to an input */
}