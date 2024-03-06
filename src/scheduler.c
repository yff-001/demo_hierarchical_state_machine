#include "scheduler.h"

#include "events.h"
#include "event_queue.h"

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
    gpio_start();
    uart0_init();
    init_timer0();
    init_timer1();

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

            communication_task();
            display_task();
            xtimer_task();
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
