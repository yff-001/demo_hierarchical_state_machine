#include <avr/io.h>
#include <util/delay.h>

#include "gpio.h"

void gpio_start() {
    DDRB |= (1 << PB5);
}

void gpio_toggle_led() {
    PORTB |= (1 << PB5);
    _delay_us(100);
    PORTB &= ~(1 << PB5);
}

void gpio_close() {
    //
}
