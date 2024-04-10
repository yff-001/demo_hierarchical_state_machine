#include "state_machine.h"
#include "events.h"
#include "event_queue.h"

#include "driver/gpio.h"
#include "handler/xtimer.h"

#define EXECUTE_ACTION(handler, triggered, state_machine)  \
do {                                                        \
    if (handler != 0) {                                     \
        result = handler(state_machine);                    \
        switch (reslut) {                                   \
            case TRIGGER_TO_SELF:                           \
                triggered = true;                           \
            case EVENT_HANDLED:                             \
                break;                                      \
            default:                                        \
                return result;                              \
        }                                                   \
    }                                                       \
} while (0)

enum operate_state_t {
    IDLE,
    MOTOR_ON,
    CHARGE
};

static enum result_t idle_action(state_machine_t* const state);
static enum result_t idle_entry(state_machine_t* const state);
static enum result_t idle_exit(state_machine_t* const state);
static enum result_t motor_on_action(state_machine_t* const state);
static enum result_t motor_on_entry(state_machine_t* const state);
static enum result_t motor_on_exit(state_machine_t* const state);
static enum result_t charge_action(state_machine_t* const state);
static enum result_t charge_entry(state_machine_t* const state);
static enum result_t charge_exit(state_machine_t* const state);

void dispatch_event(state_machine_t* const p_state_machines) {
    enum event_t event;
    event_queue_get(&event);

    /* it is possible to iterate a list of state machines */

    do {
        const state_t* p_state = p_state_machines->state;

        /* call state handler */
        enum result_t result = p_state->handler(p_state_machines);

        switch (result) {
            case EVENT_HANDLED:
                gpio_toggle_led();
                break;

            case EVENT_NOT_HANDLED:
                do {
                    // p_state = p_state -> parent;
                } while (0 /* */);
                break;

            default:
                break;

        }

        break;
    } while (1);
}

void traverse_state(state_machine_t* const p_state_machines) {
    //
}

static const state_t operate_modes[] = {
    [IDLE] = {
        .handler = idle_action,
        .entry   = idle_entry,
        .exit    = idle_exit,
        .parent  = 0,
        .child   = 0,
        .level   = 0,
    },
    [MOTOR_ON] = {
        .handler = motor_on_action,
        .entry   = motor_on_entry,
        .exit    = motor_on_exit,
        .parent  = 0,
        .child   = 0,
        .level   = 0,
    },
    [CHARGE] = {
        .handler = charge_action,
        .entry   = charge_entry,
        .exit    = charge_exit,
        .parent  = 0,
        .child   = 0,
        .level   = 0,
    }
};

void state_machine_init(state_machine_t* const p_state_machines) {
    p_state_machines->state = &operate_modes[IDLE];
    idle_entry(p_state_machines);
}

static enum result_t idle_action(state_machine_t* const state) {
    // gpio_toggle_led();
    return EVENT_HANDLED;
}

static enum result_t idle_entry(state_machine_t* const state) {
    //
}

static enum result_t idle_exit(state_machine_t* const state) {
    //
}

static enum result_t motor_on_action(state_machine_t* const state) {
    //
}

static enum result_t motor_on_entry(state_machine_t* const state) {
    //
}

static enum result_t motor_on_exit(state_machine_t* const state) {
    //
}

static enum result_t charge_action(state_machine_t* const state) {
    //
}

static enum result_t charge_entry(state_machine_t* const state) {
    //
}

static enum result_t charge_exit(state_machine_t* const state) {
    //
}
