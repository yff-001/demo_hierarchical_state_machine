#include "scheduler.h"

#include "events.h"
#include "event_queue.h"

#include "state_machine.h"

#include "driver/gpio.h"
#include "driver/timers.h"
#include "driver/uart.h"

#include "handler/communication.h"
#include "handler/display.h"
#include "handler/xtimer.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>

enum power_mode_t current_power_mode = HIGH_POWER;
// enum use_mode_t current_use_mode = USER;
// enum operate_mode_t current_operate_mode = IDLE;

enum power_mode_t get_power_mode() {
    return current_power_mode;
}

// enum use_mode_t get_use_mode() {
//     return current_use_mode;
// }

// enum operate_mode_t get_operate_mode() {
//     return current_operate_mode;
// }

state_machine_t* const sm[1];

void scheduler_init() {
    /* these should really be initialized in handlers */
    gpio_start();

    init_systick();
    init_permtick();

    /* handlers should be initialized here */
    communication_init();
    display_init();
    xtimer_init();

    xtimer_create(XTIMER_PERM, E_LED_ON, 1);

    set_sleep_mode(SLEEP_MODE_IDLE);
}

void scheduler_high_power() {
    sei();                                                                      // enable global interrupts

    while (current_power_mode == HIGH_POWER) {
        while (has_systick_elapsed() == 0 && has_permtick_elapsed() == 0 && event_queue_available() == 0) {
            sleep_mode();
        }

        if (has_permtick_elapsed() == 1) {
            timer_permtick_count();

            // display_task();
            xtimer_task(XTIMER_PERM);
        }

        if (has_systick_elapsed() == 1) {
            timer_systick_count();

            communication_task();
            // display_task();
            xtimer_task(XTIMER_SYS);
        }

        if (event_queue_available()) {
            dispatch_event(sm);                                                   // since internal of sm in the same file, seems unnecessary to pass sm pointer to function
        }
    }

    cli();                                                                      // disable global interrupts
}

void scheduler_low_power() {
    //
}

void shceduler_power_down() {
    //
}
