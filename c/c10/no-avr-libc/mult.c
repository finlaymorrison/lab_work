#include <stdint.h>

#define ADD_TO_REG(address) *(uint8_t*)(address)

#define IO_REGISTER_OFFSET 0x20
#define PORT_REGISTER_COUNT 0x3
#define DDR_OFFSET 0x1
#define PORT_OFFSET 0x2

#define ADC_OFFSET 0x78

#define INTERRUPT_CONTROL_ADD 0x69
#define INTERRUPT_MASK_ADD 0x3D

#define TIMCNT0_OFFSET 0x44
#define TIMCNTINTFLG_OFFSET 0x35

#define SUCCESS 0

void init_adc()
{
	ADD_TO_REG(ADC_OFFSET + 0x4) |= 0x40; /* Set reference to AVCC */
    ADD_TO_REG(ADC_OFFSET + 0x2) |= 0x6; /* Set prescaler to 2^6 = 64 */
    ADD_TO_REG(ADC_OFFSET + 0x2) |= 0x80; /* Enable ADC. */
	ADD_TO_REG(ADC_OFFSET + 0x2) |= 0x8; /* Enable ADC Interrupt */
	ADD_TO_REG(ADC_OFFSET + 0x2) |= 0x20; /* Enable auto-triggering */
	ADD_TO_REG(ADC_OFFSET + 0x3) |= 0x1; /* TIMER 0 compare trigger source */
}

void init_adc_timer()
{
	ADD_TO_REG(TIMCNT0_OFFSET) |= 0x2; /* Enable CTC mode */
    ADD_TO_REG(TIMCNT0_OFFSET + 0x01) |= 0x5; /* Clock TIMER0 at F_CPU / 1024 */
	ADD_TO_REG(TIMCNT0_OFFSET + 0x03) = 0; /* Start timer at 11720 Hz */
}

void init_int0()
{
    ADD_TO_REG(INTERRUPT_MASK_ADD) |= 0x1; /* Enable INT0 interrupt */
    ADD_TO_REG(INTERRUPT_CONTROL_ADD) |= 0x2; /* Trigger interrupt on falling edge */
}

void init_int1()
{
    ADD_TO_REG(INTERRUPT_MASK_ADD) |= 0x2; /* Enable INT1 interrupt */
    ADD_TO_REG(INTERRUPT_CONTROL_ADD) |= 0x8; /* Trigger interrupt on falling edge */
}

/* ADC conversion complete interrupt */
#define ADC_VECTOR __vector_24
void ADC_VECTOR ()
{
    ADD_TO_REG(TIMCNTINTFLG_OFFSET) |= 0x2; /* Resetting interrupt since TIMER0 ISR is not entered */
	ADD_TO_REG(IO_REGISTER_OFFSET + PORT_REGISTER_COUNT + PORT_OFFSET) ^= 0x128; /* Flip PB7 */

    asm("reti"); /* Return from interrupt */
}

/* Interrupt on PD2 */
#define INT0_VECTOR __vector_1
void INT0_VECTOR ()
{
    /* Increase value of OCR0A, reducing the frequency */
    uint8_t* OCR0A = &ADD_TO_REG(TIMCNT0_OFFSET + 0x03);
    if(*OCR0A < 255) *OCR0A = *OCR0A + 1;

    asm("reti"); /* Return from interrupt */
}

/* Interrupt on PD3 */
#define INT1_VECTOR __vector_2
void INT1_VECTOR ()
{
    /* Reduce value of OCR0A, increasing the frequency */
    uint8_t* OCR0A = &ADD_TO_REG(TIMCNT0_OFFSET + 0x03);
    if (*OCR0A > 0) *OCR0A = *OCR0A - 1;

    asm("reti"); /* Return from interrupt */
}

int main()
{
    /* Enable pull up resistors for interrupt pins */
    ADD_TO_REG(IO_REGISTER_OFFSET + PORT_REGISTER_COUNT * 3 + PORT_OFFSET) |= 0xC;

    /* Set PB7 as an output */
    ADD_TO_REG(IO_REGISTER_OFFSET + PORT_REGISTER_COUNT + DDR_OFFSET) |= 0x80;

    init_adc();
    init_adc_timer();
    init_int0();
    init_int1();

    asm("sei"); /* Enable global interrupts */

    while(1);

    return SUCCESS;
}