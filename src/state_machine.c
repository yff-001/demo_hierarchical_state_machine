#include "state_machine.h"
#include "events.h"
#include "event_queue.h"

#include "driver/gpio.h"
#include "handler/xtimer.h"

enum machine_state_t {
    IDLE,
    ACTIVE,
    STOP
};

enum machine_state_t current_machine_state = IDLE;

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
    event = event_queue_get(&event);
    switch (current_machine_state) {
        case IDLE:
        if (event == E_TIMER_DEFAULT) {
            gpio_toggle_led();
            current_machine_state = ACTIVE;
        }
        break;

        case ACTIVE:
        break;

        default:
        break;
    }
}
