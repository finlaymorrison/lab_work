#include <stdint.h>

#define ADD_TO_REG(address) *(uint8_t*)(address)

#define IO_REGISTER_OFFSET 0x20
#define PORT_REGISTER_COUNT 0x3
#define DDR_OFFSET 0x1
#define PORT_OFFSET 0x2

#define ADC_OFFSET 0x78

#define SUCCESS 0

void init_adc_freerun()
{
	ADD_TO_REG(ADC_OFFSET + 0x4) |= 0x40; /* Set reference to AVCC */
    ADD_TO_REG(ADC_OFFSET + 0x2) |= 0x6; /* Set prescaler to 2^6 = 64 */
    ADD_TO_REG(ADC_OFFSET + 0x2) |= 0x80; /* Enable ADC. */
	ADD_TO_REG(ADC_OFFSET + 0x2) |= 0x8; /* Enable ADC Interrupt */
	ADD_TO_REG(ADC_OFFSET + 0x2) |= 0x20; /* Enable auto-triggering */
	ADD_TO_REG(ADC_OFFSET + 0x2) |= 0x40; /* Start first conversion */
}

/* Interrupt for ADC conversion completion */
#define ADC_VECTOR __vector_24
void ADC_VECTOR ()
{
	ADD_TO_REG(IO_REGISTER_OFFSET + PORT_REGISTER_COUNT + PORT_OFFSET) ^= 0x80; /* Flip PB7 */
	asm("reti"); /* Return from interrupt */
}

int main(void)
{
	asm("sei"); /* Enable interrupt bit */
	init_adc_freerun();
	ADD_TO_REG(IO_REGISTER_OFFSET + PORT_REGISTER_COUNT + DDR_OFFSET) |= 0x80; /* Set PB7 as output */
	while (1);
	return SUCCESS;
}