#include "display.h"

#include "../driver/gpio.h"
#include <stdint.h>                     // include this before xtimer.h
#include "xtimer.h"

enum state_t {
    LED_ON,
    LED_OFF
};

enum state_t last_state;
enum state_t current_state;
enum state_t next_state;

void display_init() {
    last_state = LED_OFF;
    current_state = LED_OFF;
    next_state = LED_OFF;
}

void display_task() {
    //
    // switch (current_state) {
    //     case LED_OFF:
    //     /* entry */
    //     xtimer_create(XTIMER_PERM, E_LED_ON, 1);
    //     gpio_toggle_led();
    //     break;
    //     case LED_ON:
    //     break;
    //     default:
    //     break;
    // }
}
