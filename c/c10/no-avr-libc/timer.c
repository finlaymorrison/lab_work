#include <stdint.h>

#define ADD_TO_REG(address) *(uint8_t*)(address)

#define IO_REGISTER_OFFSET 0x20
#define PORT_REGISTER_COUNT 0x3
#define DDR_OFFSET 0x1
#define PORT_OFFSET 0x2

#define TIMCNT1_OFFSET 0x80
#define TIMCNTINT_OFFSET 0x6E

#define SUCCSESS 0

void init_seven_seg_timer()
{
	ADD_TO_REG(TIMCNT1_OFFSET + 0x1) |= 0x4; /* Clock TIMER1 at F_CPU / 256 */
	ADD_TO_REG(TIMCNT1_OFFSET + 0x1) |= 0x2; /* Enable output compare interrupt A */
	ADD_TO_REG(TIMCNT1_OFFSET + 0x1) |= 0x8; /* Enable CTC mode */
	uint16_t TOP = 46875; /* Fills up at a rate of 1Hz */
	ADD_TO_REG(TIMCNT1_OFFSET + 0x9) = TOP / 8; /* Setting OCR1AH */
	ADD_TO_REG(TIMCNT1_OFFSET + 0x8) = TOP % 8; /* Setting OCR1AL */
}

const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};
volatile uint8_t count;

/* Interrupt for when TIMER1 reaches its OCRA value */
#define TIMER1_COMPA_VECTOR __vector_13
void TIMER1_COMPA_VECTOR ()
{
	++count;
	if (count > 9) count = 0;

	/* setting the value on the seven segment display */
	ADD_TO_REG(IO_REGISTER_OFFSET + PORT_OFFSET) = segments[count];

	asm("reti"); /* Return from interrupt */
}

int main(void)
{
	/* Setting the seven segment pins as outputs */
	ADD_TO_REG(IO_REGISTER_OFFSET + DDR_OFFSET) = 0xFF;
	/* Initialising display to 0 */
	count = 0;
	ADD_TO_REG(IO_REGISTER_OFFSET + PORT_OFFSET) = segments[count];

	/* Initializing timer that updates the seven segment display */
	init_seven_seg_timer();

	asm("sei"); /* Enable interrupt bit */

	while (1);
    
    return SUCCSESS;
}