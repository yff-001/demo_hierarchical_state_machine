#include "demo_hsm.h"
// #include "state_machine.h"

static enum result_t user_action(state_machine_t* const state);
static enum result_t user_entry(state_machine_t* const state);
static enum result_t user_exit(state_machine_t* const state);
static enum result_t service_action(state_machine_t* const state);
static enum result_t service_entry(state_machine_t* const state);
static enum result_t service_exit(state_machine_t* const state);
static enum result_t idle_action(state_machine_t* const state);
static enum result_t idle_entry(state_machine_t* const state);
static enum result_t idle_exit(state_machine_t* const state);
static enum result_t motor_run_action(state_machine_t* const state);
static enum result_t motor_run_entry(state_machine_t* const state);
static enum result_t motor_run_exit(state_machine_t* const state);
static enum result_t charge_action(state_machine_t* const state);
static enum result_t charge_entry(state_machine_t* const state);
static enum result_t charge_exit(state_machine_t* const state);

static const state_t USER = {
    .entry   = user_entry,
    .exit    = user_exit,
    .handler = user_action,
    .parent  = 0,
};

static const state_t SERVICE = {
    .entry   = service_entry,
    .exit    = service_exit,
    .handler = service_action,
    .parent  = 0,
};

static const state_t IDLE = {
    .entry   = idle_entry,
    .exit    = idle_exit,
    .handler = idle_action,
    .parent  = &USER,
};

static const state_t MOTOR_RUN = {
    .entry   = motor_run_entry,
    .exit    = motor_run_exit,
    .handler = motor_run_action,
    .parent  = &USER,
};

static const state_t CHARGE = {
    .entry   = charge_entry,
    .exit    = charge_exit,
    .handler = charge_action,
    .parent  = &USER,
};

void state_machine_init(state_machine_t* const p_state_machines) {
    p_state_machines->state = &USER;
}

static enum result_t idle_action(state_machine_t* const state) {
    // gpio_toggle_led();
    return EVENT_HANDLED;
}

static enum result_t user_action(state_machine_t* const state) {
    //
}

static enum result_t user_entry(state_machine_t* const state) {
    //
}

static enum result_t user_exit(state_machine_t* const state) {
    //
}

static enum result_t service_action(state_machine_t* const state) {
    //
}

static enum result_t service_entry(state_machine_t* const state) {
    //
}

static enum result_t service_exit(state_machine_t* const state) {
    //
}

static enum result_t idle_entry(state_machine_t* const state) {
    //
}

static enum result_t idle_exit(state_machine_t* const state) {
    //
}

static enum result_t motor_run_action(state_machine_t* const state) {
    //
}

static enum result_t motor_run_entry(state_machine_t* const state) {
    //
}

static enum result_t motor_run_exit(state_machine_t* const state) {
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
