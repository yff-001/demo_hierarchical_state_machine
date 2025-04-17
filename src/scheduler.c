#include "scheduler.h"

#include "log.h"

#include "events.h"
#include "event_queue.h"

#include "state_machine.h"

#include "driver/adc.h"
#include "driver/cpu.h"
#include "driver/gpio.h"
#include "driver/pwm.h"
#include "driver/timers.h"
#include "driver/uart.h"

#include "device/ssd1312.h"

#include "handler/communication.h"
#include "handler/dac.h"
#include "handler/display.h"
#include "handler/measure.h"
#include "handler/xtimer.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>

enum power_mode_t current_power_mode = HIGH_POWER;

enum power_mode_t get_power_mode() {
    return current_power_mode;
}

int count = 0;

state_machine_t machine;

void scheduler_init() {
    /* these should really be initialized in handlers */
    gpio_start();
    pwm_init();

    init_systick();
    init_permtick();

    /* handlers should be initialized here */
    communication_init();
    display_init();
    measure_init();
    xtimer_init();

    state_machine_init(&machine);

    xtimer_create(XTIMER_PERM, E_LED_ON, 10);

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

            if (count++ > 3) {
                dac_set_voltage();
                count = 0;
                gpio_toggle_led();
            }

            // gpio_toggle_led();
            xtimer_task(XTIMER_PERM);

            LOG_INFO("perm tick\n");
        }

        if (has_systick_elapsed() == 1) {
            timer_systick_count();
            cpu_watchdog_timer_reset();

            // gpio_toggle_led();
            // communication_task();
            // display_task();
            xtimer_task(XTIMER_SYS);
        }

        if (event_queue_available()) {
            dispatch_event(&machine);
        }
    }

    cpu_watchdog_timer_reset();
    cli();                                                                      // disable global interrupts
}

void scheduler_low_power() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
}

void shceduler_power_down() {
    //
}

void set_power_mode(enum power_mode_t mode) {
    current_power_mode = LOW_POWER;
}
