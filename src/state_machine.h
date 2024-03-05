#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

/*  this is an attempt to write my own state machine implementation */

enum state_machine_result_t {
    EVENT_HANDLED,
    EVENT_NOT_HANDLED,
    TRIGGER_TO_SELF
};

// typedef state_machine_result_t (*state_handler) (state_machine_t* const state);
// struct state_t {

// }

// /* abstract state machine structure */
// struct state_machine_t {
//     uint32_t event;
//     const state_t* state;
// };

void state_machine_active();
void state_machine_idle();

#endif
