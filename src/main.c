// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <avr/pgmspace.h>
// #include <avr/sleep.h>
// #include <avr/wdt.h>
// #include <util/delay.h>

// #include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#include "device.h"
#include "events.h"
#include "event_queue.h"
#include "scheduler.h"
// #include "state_machine.h"


int main() {
    init_device();

    enum power_mode_t current_power_mode = HIGH_POWER;
    enum use_mode_t current_use_mode = USER;
    enum operate_mode_t current_operate_mode = IDLE;

    for (;;) {
        switch (0) {
            case HIGH_POWER:
                scheduler_high_power();
                switch (0) {
                    case USER:
                        // switch (current_operate_mode) {
                        //     case IDLE:
                        //         break;
                        //     case ACTIVE:
                        //         break;
                        //     case CHARGE:
                        //         break;
                        //     default:
                        //         break;
                        // }
                        break;
                    case SERVICE:
                        break;
                    default:
                        break;
                }
                // current_power_mode = LOW_POWER;
                break;
            case LOW_POWER:
                scheduler_low_power();
                // current_power_mode = HIGH_POWER;
                break;
            case POWER_DOWN:
                shceduler_power_down();
                break;
            default:
                break;
        }
    }
}
