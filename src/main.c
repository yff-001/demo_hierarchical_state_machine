#include "scheduler.h"

int main() {
    scheduler_init();

    for (;;) {
        switch (get_power_mode()) {
            case HIGH_POWER:
                scheduler_high_power();
                break;
            case LOW_POWER:
                scheduler_low_power();
                break;
            case POWER_DOWN:
                shceduler_power_down();
                break;
            default:
                break;
        }
    }
}
