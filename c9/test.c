#include <stdint.h>
#include <avr/io.h>

void select_adc_input(uint8_t input_number)
{
    ADMUX &= 0xF0 | input_number;
}

void init_adc()
{
    /* Set prescaler to 2^6 = 64 */
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
    /* Enable ADC */
    ADCSRA |= _BV(ADEN);
}

void wait_for_adc_conversion_to_complete()
{
    /* Loop until the ADSC bit has been cleared on the ADCSRA register */
    loop_until_bit_is_clear(ADCSRA, ADSC);
}

void init_adc_auto_trigger()
{
    /* Set prescaler to 2^6 = 64 */
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
    /* Enable ADC */
    ADCSRA |= _BV(ADEN);

    /* Enable ADC auto triggering */
    ADCSRA |= _BV(ADATE);
    /* Start first conversion */
    ADCSRA |= _BV(ADSC);
}

void enable_free_running_mode()
{
    /* Clearing the ADTS2 ADTS1 and ADTS0 bits on the ADCSRB register */
    ADCSRB &= ~(_BV(ADTS2) | _BV(ADTS1) | _BV(ADTS0));
}

void trigger_eir0()
{
    ADCSRB |= _BV(ADTS0);
}

void start_adc_conversion()
{
    /* Setting the start conversion bit on ACDSRA */
    ADCSRA |= _BV(ADSC);
}

int main(void)
{

}