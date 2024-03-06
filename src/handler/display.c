#include "display.h"
#include "../driver/gpio.h"

void display_task() {
    //
    gpio_toggle_led();
}