#ifndef SCHEDULER_H
#define SCHEDULER_H

enum power_mode_t {
    HIGH_POWER,
    LOW_POWER,
    POWER_DOWN
};

enum use_mode_t {
    USER,
    SERVICE
};

enum operate_mode_t {
    IDLE,
    ACTIVE,
    CHARGE
};

// enum power_mode_t current_power_mode = HIGH_POWER;
// enum use_mode_t current_use_mode = USER;
// enum operate_mode_t current_operate_mode = IDLE;

void scheduler_init();
void scheduler_high_power();
void scheduler_low_power();
void shceduler_power_down();
void dispatch_event();

#endif