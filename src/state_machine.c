#include "state_machine.h"
#include "events.h"
#include "event_queue.h"

void state_machine_active() {
    //
    for (;;) {
        //
    }
}

void state_machine_idle() {
    //
    for (;;) {
        //
    }
}

void run_state_machine() {
    enum event_t event;
    event = event_queue_get(&event);
    switch (event) {
        case 0:
        break;
    }
}
