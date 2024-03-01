#include <avr/io.h>

#include "gpio.h"

void gpio_start() {
    DDRB |= (1 << PB5);
}

void gpio_close() {
    //
}