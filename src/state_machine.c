#include "state_machine.h"
#include "events.h"
#include "event_queue.h"

#include "driver/gpio.h"
#include "handler/xtimer.h"

enum operate_state_t {
    IDLE,
    MOTOR_ON,
    CHARGE
};

enum result_t {
    EVENT_HANDLED,
    EVENT_UNHANDLED,
    TRIGGER_TO_SELF
};

static void idle_handler(state_machine_t* const state);
static void idle_entry(state_machine_t* const state);
static void idle_exit(state_machine_t* const state);
static void motor_on_handler(state_machine_t* const state);
static void motor_on_entry(state_machine_t* const state);
static void motor_on_exit(state_machine_t* const state);
static void charge_handler(state_machine_t* const state);
static void charge_entry(state_machine_t* const state);
static void charge_exit(state_machine_t* const state);

void dispatch_event(state_machine_t* const p_state_machines[]) {
    /* it is possible to iterate a list of state machines */

    do {
        /* call state handler */

        switch (0) {
            case EVENT_HANDLED:

            break;

            case EVENT_UNHANDLED:
            do {
                // p_state = p_state -> parent;
            } while (0 /* */);
            break;

            default:
            break;

        }
    } while (1);
}

void traverse_state(state_machine_t* const p_state_machines[]) {
    //
}

static const state_t operate_modes[] = {
    [IDLE] = {
        .handler = idle_handler,
        .entry   = idle_entry,
        .exit    = idle_exit,
        .parent  = 0,
        .child   = 0,
        .level   = 0,
    },
    [MOTOR_ON] = {
        .handler = motor_on_handler,
        .entry   = motor_on_entry,
        .exit    = motor_on_exit,
        .parent  = 0,
        .child   = 0,
        .level   = 0,
    },
    [CHARGE] = {
        .handler = charge_handler,
        .entry   = charge_entry,
        .exit    = charge_exit,
        .parent  = 0,
        .child   = 0,
        .level   = 0,
    }
};

static void idle_handler(state_machine_t* const state) {
    //
}

static void idle_entry(state_machine_t* const state) {
    //
}

static void idle_exit(state_machine_t* const state) {
    //
}

static void motor_on_handler(state_machine_t* const state) {
    //
}

static void motor_on_entry(state_machine_t* const state) {
    //
}

static void motor_on_exit(state_machine_t* const state) {
    //
}

static void charge_handler(state_machine_t* const state) {
    //
}

static void charge_entry(state_machine_t* const state) {
    //
}

static void charge_exit(state_machine_t* const state) {
    //
}
