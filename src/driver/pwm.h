#ifndef PWM_H
#define PWM_H

#include <stdint.h>

void pwm_init();

void pwm_set_dutycycle(uint16_t duty);

#endif
