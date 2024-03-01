#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

/*  this is an attempt to write my own state machine implementation */

enum state_t {
    ACTIVE,
    IDLE
};

enum event_t {
    _abort,
    _start
};

struct state_machine_t {
    // state handler
    // entry action
    // exit action
};

void state_machine_active();
void state_machine_idle();

#endif