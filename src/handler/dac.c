#include "dac.h"

#include "../driver/pwm.h"

#include <stdint.h>

void dac_init() {
    // 
}

void dac_set_voltage() {
    static uint16_t code = 0;

    pwm_set_dutycycle(code);

    code += 0x43;
}
