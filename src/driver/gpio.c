#include <avr/io.h>
#include <util/delay.h>

#include "gpio.h"

void gpio_start() {
    DDRB |= (1 << PB5);

    /* PWM output on timer 1 */
    // DDRB |= (1 << PB1);         // OC1A
    // DDRB |= (1 << PB2);         // OC1B

    /* PWM output on timer 2 */
    // DDRB |= (1 << PB3);         // OC2A
    // DDRD |= (1 << PD3);         // OC2B

    DDRD |= (1 << PD5);         // OC0B
    DDRD |= (1 << PD6);         // OC0A
}

void gpio_toggle_led() {
    PORTB |= (1 << PB5);
    _delay_us(100);
    PORTB &= ~(1 << PB5);
}

void gpio_close() {
    //
}
