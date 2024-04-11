#include "state_machine.h"

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

void dispatch_event(state_machine_t* const p_state_machines) {
    /* it is possible to iterate a list of state machines */

    do {
        const state_t* p_state = p_state_machines->state;

        /* call state handler */
        enum result_t result = p_state->handler(p_state_machines);

        switch (result) {
            case EVENT_HANDLED:

                break;

            /* specific to a hierarchical state machine */
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
