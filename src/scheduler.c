#include "scheduler.h"

#include "events.h"
#include "event_queue.h"
#include "state_machine.h"

#include "driver/gpio.h"
#include "driver/timers.h"
#include "driver/uart.h"

#include "handler/communication.h"
#include "handler/display.h"
#include "handler/soft_timer.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>

enum power_mode_t current_power_mode = HIGH_POWER;
enum use_mode_t current_use_mode = USER;
enum operate_mode_t current_operate_mode = IDLE;

enum power_mode_t get_power_mode() {
    return HIGH_POWER;
}

enum use_mode_t get_use_mode() {
    return USER;
}

enum operate_mode_t get_operate_mode() {
    return IDLE;
}

void scheduler_init() {
    /* these should really be initialized in handlers */
    // gpio_start();
    // uart0_init();
    // init_timer0();
    // init_timer1();

    /* handlers should be initialized here */

    set_sleep_mode(SLEEP_MODE_IDLE);
    // sei();
}

void scheduler_high_power() {
    sei();                                                                      // enable global interrupts
    for (;;) {
        while (has_timer0_ticked() == 0 && has_timer0_ticked() == 0 && event_queue_available() == 0) {
            sleep_mode();
        }

        if (has_timer1_ticked() == 1) {
            timer1_tick_count();
            xtimer_task(XTIMER_PERM);
        }

        if (has_timer0_ticked() == 1) {
            timer0_tick_count();

            communication_task();
            display_task();
            xtimer_task(XTIMER_SYS);
        }

        run_state_machine();
    }
    cli();                                                                      // disable global interrupts
}

void scheduler_low_power() {
    //
}

void shceduler_power_down() {
    //
}

// void dispatch_event() {

// }
