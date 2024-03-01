// #include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adc.h"
#include "event_queue.h"
#include "gpio.h"
#include "scheduler.h"
#include "state_machine.h"
#include "timers.h"
#include "uart.h"

void init_system();

int main() {
    init_system();

    // uart0_puts("hello world\r\n");

    enum state_t current_state = ACTIVE;

    for (;;) {
        while (has_timer0_ticked() == 0) {
            sleep_mode();
        }

        while (has_timer0_ticked() == 1) {
            timer0_tick_count();
            switch (current_state) {
                case ACTIVE:
                    PORTB |= (1 << PB5);
                    current_state = IDLE;
                    break;
                case IDLE:
                    PORTB &= ~(1 << PB5);
                    current_state = ACTIVE;
                    break;
                default:
                    break;
            }
        }

        dispatch_event();                               // placeholder function
    }
}

void init_system() {
    gpio_start();
    uart0_init();
    init_timer0();
    init_timer1();

    set_sleep_mode(SLEEP_MODE_IDLE);
    sei();
}