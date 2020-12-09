void enable_free_running_mode()
{
    ADCSRB &= ~(_BV(ADTS2) | _BV(ADTS1) | _BV(ADTS0));
    ADCSRA |= _BV(ADETE);
}