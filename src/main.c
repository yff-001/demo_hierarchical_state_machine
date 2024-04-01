#include "device.h"
// #include "events.h"
// #include "event_queue.h"
#include "scheduler.h"

int main() {
    scheduler_init();

    for (;;) {
        switch (get_power_mode()) {
            case HIGH_POWER:
                scheduler_high_power();
                switch (get_use_mode()) {
                    case USER:
                        switch (get_operate_mode()) {
                            case IDLE:
                                break;
                            case ACTIVE:
                                break;
                            case CHARGE:
                                break;
                            default:
                                break;
                        }
                        break;
                    case SERVICE:
                        break;
                    default:
                        break;
                }
                // current_power_mode = LOW_POWER;
                break;
            case LOW_POWER:
                scheduler_low_power();
                // current_power_mode = HIGH_POWER;
                break;
            case POWER_DOWN:
                shceduler_power_down();
                break;
            default:
                break;
        }
    }
}
