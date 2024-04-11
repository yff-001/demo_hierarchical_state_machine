#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdint.h>

enum result_t {
    EVENT_HANDLED,
    EVENT_NOT_HANDLED,
    // TRIGGER_TO_SELF             // not considered for now
};

typedef struct state_t state_t;
typedef struct state_machine_t state_machine_t;
typedef enum result_t (*action)(struct state_machine_t* state);

struct state_t {
    action entry;
    action exit;
    action handler;

    const state_t* const parent;
};

struct state_machine_t {
    const state_t* state;
};

void dispatch_event(state_machine_t* const p_state_machines);
void traverse_state(state_machine_t* const p_state_machines);



#endif
