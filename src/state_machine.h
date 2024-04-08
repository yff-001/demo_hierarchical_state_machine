#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdint.h>

typedef struct state_t state_t;
typedef struct state_machine_t state_machine_t;
typedef void (*state_handler)(struct state_machine_t* state);

struct state_t {
    state_handler handler;
    state_handler entry;
    state_handler exit;

    const state_t* const parent;
    const state_t* const child;
    uint8_t level;
};

struct state_machine_t {
    uint8_t event;
    const state_t* state;
};

void dispatch_event(state_machine_t* const p_state_machines[]);
void traverse_state(state_machine_t* const p_state_machines[]);

#endif
