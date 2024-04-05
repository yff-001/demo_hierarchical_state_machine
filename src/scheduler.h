#ifndef SCHEDULER_H
#define SCHEDULER_H

enum power_mode_t {
    HIGH_POWER,
    LOW_POWER,
    POWER_DOWN
};

// enum use_mode_t {
//     USER,
//     SERVICE
// };

// enum operate_mode_t {
//     IDLE,
//     ACTIVE,
//     CHARGE
// };

enum power_mode_t get_power_mode();
// enum use_mode_t get_use_mode();
// enum operate_mode_t get_operate_mode();

void scheduler_init();
void scheduler_high_power();
void scheduler_low_power();
void shceduler_power_down();

#endif
