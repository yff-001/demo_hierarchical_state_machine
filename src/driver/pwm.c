#include <avr/io.h>

#include "pwm.h"

void pwm_init() {
    // TCCR1A |= (1 << COM1A1);
    // TCCR1A |= (1 << COM1B1);

    // /* ICR1 used as TOP */
    // TCCR1B |= (1 << WGM13);

    // TCCR1B |= (1 << CS10);
    
    // TIMSK1 |= (1 << OCIE1A);
    // TIMSK1 |= (1 << OCIE1B);

    // ICR1 = 0xFFFF;

    // OCR1A = 32767;
    // OCR1B = 16383;

    // TCCR2A |= (1 << COM2A1);
    // TCCR2A |= (1 << COM2B1);

    // TCCR2A |= (1 << WGM20);

    // TCCR2B |= (1 << CS20);

    // OCR2A = 51;             // D11
    // OCR2B = 125;            // D3

    TCCR0A |= (1 << COM0A1);
    TCCR0A |= (1 << COM0B1);

    TCCR0A |= (1 << WGM00);             // phase correct pwm

    TCCR0B |= (1 << CS00);              // prescaler = 1
}

void pwm_set_dutycycle(uint16_t duty) {
    OCR0A = (uint8_t)(duty >> 8);       // channel A gets assigned higher byte, 3.9kOhm resistor attached
    OCR0B = (uint8_t)(duty & 0xFF);     // channel B gets assigned lower byte, 1MOhm resistor attached
}
