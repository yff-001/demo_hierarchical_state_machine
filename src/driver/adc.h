#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adc_init();
void adc_disable();
void adc_register_callback(void (*callback)(uint16_t));
void adc_start();
void adc_stop();

#endif
