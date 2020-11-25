#include "spi.h"
#include "digitalPot.h"

#include <util/delay.h>

int main(void)
{
	/* Initializing the digital potentiometer */
	init_pot();

	uint8_t num = 0;

	while (1)
	{
		/* Looping back around once it gets to 255 */
		if (num == 255)
		{
			setXpot(0x0);
			num = 0;
		}
		else
		incXpot();
		++num;
		_delay_ms(1);
	}
}