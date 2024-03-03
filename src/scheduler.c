#include "scheduler.h"

#include "events.h"
#include "event_queue.h"

#include "driver/timers.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>

enum power_mode_t current_power_mode = HIGH_POWER;
enum use_mode_t current_use_mode = USER;
enum operate_mode_t current_operate_mode = IDLE;

void scheduler_init() {
    set_sleep_mode(SLEEP_MODE_IDLE);
    sei();
}

void scheduler_high_power() {
    // event_queue_available();
    // event_queue_get(&e);
    
    for (;;) {
        while (has_timer0_ticked() == 0) {
            sleep_mode();
        }

        while (has_timer0_ticked() == 1) {
            timer0_tick_count();
            // switch (current_state) {
            //     case ACTIVE:
            //         PORTB |= (1 << PB5);
            //         current_state = IDLE;
            //         break;
            //     case IDLE:
            //         PORTB &= ~(1 << PB5);
            //         current_state = ACTIVE;
            //         break;
            //     default:
            //         break;
            // }
        }
    }
}

void scheduler_low_power() {
    //
}

void shceduler_power_down() {
    //
}

void dispatch_event() {
    //
}
