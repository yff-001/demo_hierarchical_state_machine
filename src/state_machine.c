#include "state_machine.h"
#include "events.h"
#include "event_queue.h"

#include "driver/gpio.h"
#include "handler/xtimer.h"

enum machine_state_t {
    USER,
    SERVICE,
    IDLE,
    ACTIVE,
    CHARGE
};

enum comm_state_t {
    COMM_IDLE,
    C1,
    C2,
    C3
};

static enum machine_state_t current_machine_state = USER;

static enum comm_state_t comm_last_state = C1;
static enum comm_state_t comm_current_state = C1;
static enum comm_state_t comm_next_state = C1;

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
        case USER:
        /* ENTRY */
        if (event == E_BUTTON_PRESS) {
            gpio_toggle_led();
            current_machine_state = IDLE;
            xtimer_create(XTIMER_PERM, E_LED_ON, 1);
        }
        /* EXIT */
        break;

        case SERVICE:
        break;

        case IDLE:
        break;

        case ACTIVE:
        break;

        case CHARGE:
        break;

        default:
        break;
    }

    do
    {
        comm_current_state = comm_next_state;

        /* code */

        comm_last_state = comm_current_state;
    } while (comm_current_state != comm_next_state);
}
