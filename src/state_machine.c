#include "state_machine.h"
#include "events.h"
#include "event_queue.h"

#include "driver/gpio.h"
#include "handler/xtimer.h"

#define TAKE_ACTION(handler, triggered, state_machine)     \
do {                                                        \
    if (handler != 0) {                                     \
        enum result_t result = handler(state_machine);                    \
        switch (result) {                                   \
            case TRIGGER_TO_SELF:                           \
                triggered = 1;                           \
            case EVENT_HANDLED:                             \
                break;                                      \
            default:                                        \
                return result;                              \
        }                                                   \
    }                                                       \
} while (0)

enum user_state_t {
    USER,
    SERVICE
};

enum operate_state_t {
    IDLE,
    MOTOR_ON,
    CHARGE
};

static enum result_t user_action(state_machine_t* const state);
static enum result_t user_entry(state_machine_t* const state);
static enum result_t user_exit(state_machine_t* const state);
static enum result_t service_action(state_machine_t* const state);
static enum result_t service_entry(state_machine_t* const state);
static enum result_t service_exit(state_machine_t* const state);
static enum result_t idle_action(state_machine_t* const state);
static enum result_t idle_entry(state_machine_t* const state);
static enum result_t idle_exit(state_machine_t* const state);
static enum result_t motor_on_action(state_machine_t* const state);
static enum result_t motor_on_entry(state_machine_t* const state);
static enum result_t motor_on_exit(state_machine_t* const state);
static enum result_t charge_action(state_machine_t* const state);
static enum result_t charge_entry(state_machine_t* const state);
static enum result_t charge_exit(state_machine_t* const state);

enum result_t dispatch_event(state_machine_t* const p_state_machines) {
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
                    if (p_state->parent == 0) {
                        return EVENT_NOT_HANDLED;
                    }
                    p_state = p_state->parent;
                } while (p_state->handler == 0);
                continue;

            default:
                return result;
        }

        break;
    } while (1);
}

enum result_t traverse_state(state_machine_t* const p_state_machines, const state_t* p_target_state) {
    const state_t* p_source_state = p_state_machines->state;
    p_state_machines->state = p_target_state;

    int trigger_to_self = 0;

    const state_t* p_target_path[5];
    uint8_t index = 0;

    if (p_source_state->level > p_target_state->level) {
        /* traverse up the hierarchy */
        while (p_source_state->level > p_target_state->level) {
            TAKE_ACTION(p_source_state->exit, trigger_to_self, p_state_machines);
            p_source_state = p_source_state->parent;
        }
    }
    else if (p_source_state->level < p_target_state->level) {
        /* traverse down the hierarchy */
        while (p_source_state->level < p_target_state->level) {
            p_target_path[index++] = p_target_state;
            p_target_state = p_target_state->parent;
        }
    }

    while (p_source_state->parent != p_target_state->parent) {
        TAKE_ACTION(p_source_state->exit, trigger_to_self, p_state_machines);
        p_source_state = p_source_state->parent;
        p_target_path[index++] = p_target_state;
        p_target_state = p_target_state->parent;
    }

    TAKE_ACTION(p_source_state->exit, trigger_to_self, p_state_machines);
    TAKE_ACTION(p_target_state->entry, trigger_to_self, p_state_machines);

    while (index) {
        index--;
        TAKE_ACTION(p_target_path[index]->entry, trigger_to_self, p_state_machines);
    }

    if (trigger_to_self == 1) {
        return TRIGGER_TO_SELF;
    }
    else {
        return EVENT_HANDLED;
    }
}

/* states on the same level are grouped in an array */
static const state_t user_modes[2];
static const state_t operate_modes[3];

static const state_t user_modes[] = {
    [USER] = {
        .handler = user_action,
        .entry   = user_entry,
        .exit    = user_exit,
        .parent  = 0,
        .child   = operate_modes,
        .level   = 0,
    },
    [SERVICE] = {
        .handler = service_action,
        .entry   = service_entry,
        .exit    = service_exit,
        .parent  = 0,
        .child   = 0,
        .level   = 0,
    }
};

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
    p_state_machines->state = &user_modes[USER];
    user_entry(p_state_machines);
}

static enum result_t user_action(state_machine_t* const state) {
    switch (state->event) {
        case E_COMM_START:
        traverse_state(state, &user_modes[SERVICE]);
        break;
        default:
        break;
    }

    return EVENT_HANDLED;
}

static enum result_t user_entry(state_machine_t* const state) {
    return EVENT_HANDLED;
}

static enum result_t user_exit(state_machine_t* const state) {
    //
    return EVENT_HANDLED;
}

static enum result_t service_action(state_machine_t* const state) {
    //
    return EVENT_HANDLED;
}

static enum result_t service_entry(state_machine_t* const state) {
    //
    return EVENT_HANDLED;
}

static enum result_t service_exit(state_machine_t* const state) {
    //
    return EVENT_HANDLED;
}

static enum result_t idle_action(state_machine_t* const state) {
    return EVENT_HANDLED;
}

static enum result_t idle_entry(state_machine_t* const state) {
    return EVENT_HANDLED;
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
