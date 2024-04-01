#include "state_machine.h"
#include "events.h"
#include "event_queue.h"

#include "driver/gpio.h"
#include "handler/xtimer.h"

enum machine_state_t {
    S1,
    S2,
    S3
};

enum machine_state_t current_machine_state = S1;

void state_machine_active() {
    //
    for (;;) {
        //
    }
}

void state_machine_idle() {
    //
    for (;;) {
        //
    }
}

void dispatch_event() {
    enum event_t event;
    event_queue_get(&event);
    switch (current_machine_state) {
        case S1:
        if (event == E_LED_ON) {
            gpio_toggle_led();
            // current_machine_state = S2;
            xtimer_create(XTIMER_PERM, E_LED_ON, 1);
        }
        break;

        case S2:
        break;

        default:
        break;
    }
}
