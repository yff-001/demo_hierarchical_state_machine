#include "measure.h"

#include <stdlib.h>
#include <stdint.h>

#include "../driver/adc.h"
#include "../driver/uart.h"

static uint16_t temperature_raw;
static void sample_temperature(uint16_t data);

void measure_init() {
    adc_register_callback(sample_temperature);
}

void measure_disable() {
    // 
}

void measure_start() {
    // 
}

void measure_stop() {
    // 
}

void measure_task() {
    static uint8_t count = 0;
    char message[10] = {0};

    if (count++ == 200) {
        count = 0;
        utoa(temperature_raw, message, 10);
        uart0_puts(message);
        uart0_puts("\r\n");
    }
}

static void sample_temperature(uint16_t data) {
    temperature_raw = data;
}
