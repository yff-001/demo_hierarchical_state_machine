#include "twi.h"

#include <avr/io.h>

#define F_SCL   (400000)

void twi_init() {
    /* or leave TWBR as 0
        so f = 1000000 Hz*/
    TWBR = ((F_CPU / F_SCL) - 16) / 2;
    TWCR |= (1 << TWEN);

    // PORTC |= (1 << PC4) | (1 << PC5);
}

void twi_start() {
    // 
}

void twi_write_data(uint8_t data) {
    // 
}

void twi_stop() {
    // 
}
