#include <stdint.h>

#define ADD_TO_REG(address) *(uint8_t*)(address)

#define IO_REGISTER_OFFSET 0x20
#define PORT_REGISTER_COUNT 0x3
#define DDR_OFFSET 0x1
#define PORT_OFFSET 0x2

#define INTERRUPT_CONTROL_ADD 0x69
#define INTERRUPT_MASK_ADD 0x3D

#define JTAG_REG_ADD 0x55

#define SUCCESS 0

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

volatile uint8_t num;

/* Interrupt on PD2 (INT0) */
#define INT0_VECTOR __vector_1
void INT0_VECTOR ()
{
    uint8_t* PORTC = &ADD_TO_REG(IO_REGISTER_OFFSET + PORT_REGISTER_COUNT * 2 + PORT_OFFSET);
    if (*PORTC > 0) *PORTC = *PORTC - 1;

    asm("reti"); /* Return from interrupt */
}

/* Interrupt on PD3 (INT1) */
#define INT1_VECTOR __vector_2
void INT1_VECTOR ()
{
    uint8_t* PORTC = &ADD_TO_REG(IO_REGISTER_OFFSET + PORT_REGISTER_COUNT * 2 + PORT_OFFSET);
    if (*PORTC < 255) *PORTC = *PORTC + 1;

    asm("reti"); /* Return from interrupt */
}

int main()
{
    /* Disabling the JTAG interface in order to use PC2-PC5.
     * Need to set the JTD bit in the MCUCR register twice in
     * the space of 4 clock cycles. */
    ADD_TO_REG(JTAG_REG_ADD) |= 0x80;
    ADD_TO_REG(JTAG_REG_ADD) |= 0x80;

    num = 0;

    ADD_TO_REG(IO_REGISTER_OFFSET + PORT_REGISTER_COUNT * 2 + DDR_OFFSET) = 0xFF;
    ADD_TO_REG(IO_REGISTER_OFFSET + PORT_REGISTER_COUNT * 2 + PORT_OFFSET) = 0;

    /* Enable pull up resistors on interrupt pins */
    ADD_TO_REG(IO_REGISTER_OFFSET + PORT_REGISTER_COUNT * 3 + PORT_OFFSET) |= 0xC;

    init_int0();
    init_int1();

    asm("sei"); /* Enable global interrupts */

    while(1);

    return SUCCESS;
}