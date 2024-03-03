#include <stdint.h>
#include <stdbool.h>

#include "soft_timer.h"
// #include "events.h"

#define MAX_NUMBER_PERM 5
#define MAX_NUMBER_SYS  10

struct timer_t {
    uint32_t duration;
    enum event_t event;
    bool is_suspended;
};

struct timer_t timers[MAX_NUMBER_PERM + MAX_NUMBER_SYS];

/* function prototype */
static bool create_timer(const enum xtimer_t timer_type, const enum event_t event, const uint32_t duration);

void xtimer_init() {
    for (uint8_t index = 0; index < (MAX_NUMBER_PERM + MAX_NUMBER_SYS); index++) {
        timers[index].duration = 0;
        timers[index].event = E_VOID;
        timers[index].is_suspended = false;
    }
}

void xtimer_create(const enum xtimer_t timer_type, const enum event_t event, const uint32_t duration) {
    
}

void xtimer_cancel(const enum xtimer_t timer_type, const enum event_t event) {

}

static bool create_timer(const enum xtimer_t timer_type, const enum event_t event, const uint32_t duration) {
    uint8_t index;
    /* iterate the array of timers based on timer_type */
    // for (index)
}
