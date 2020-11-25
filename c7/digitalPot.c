/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */

#include "spi.h"
#include "digitalPot.h"

void init_pot(void)
{
    /* Initializing the spi interface. */
	init_spi_master();
    /* Starting the wipers at 0. */
    setXpot(0x0);
    setYpot(0x0);
}

void decXpot(void)
{
    spi_tx(0x8);
}

void incXpot(void)
{
    spi_tx(0x4);
}

void decYpot(void)
{
    spi_tx(0x18);
}

void incYpot(void)
{
    spi_tx(0x14);
}

void setXpot(uint8_t x)
{
    spi_tx(0x0);
    spi_tx(x);
}

void setYpot(uint8_t y)
{
    spi_tx(0x10);
    spi_tx(y);
}