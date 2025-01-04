#include <avr/interrupt.h>
#include <avr/io.h>

#include "adc.h"

void (*write_data)(uint16_t);

void adc_init() {
    /*
        REFS1   REFS0
        0       0       AREF, internal vref turned off
        0       1       AVCC
        1       0       reserved
        1       1       internal voltage reference
    */
    ADMUX |= (1 << REFS0);
    ADMUX |= (1 << REFS1);

    // ADMUX |= (1 << ADLAR);              // left aligned

    /* channel selection */
    ADMUX |= (1 << MUX3);
    // ADMUX |= (1 << MUX2);
    // ADMUX |= (1 << MUX1);
    // ADMUX |= (1 << MUX0);
    
    /* 
        adc prescaler
        ADPS2   ADPS1   ADPS0
        0       0       0       2
        0       0       1       2
        0       1       0       4
        0       1       1       8
        1       0       0       16
        1       0       1       32
        1       1       0       64
        1       1       1       128
    */
    ADCSRA |= (1 << ADPS2);
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 << ADPS0);
    
    ADCSRA |= (1 << ADATE);             // enable auto trigger
    ADCSRA |= (1 << ADIE);              // enable interrupt

    ADCSRA |= (1 << ADEN);              // enable adc
}

void adc_diable() {
    ADCSRA &= ~(1 << ADEN);
}

void adc_register_callback(void (*callback)(uint16_t)) {
    write_data = callback;
}

void adc_start() {
    // ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADSC);
}

void adc_stop() {
    // ADCSRA &= ~(1 << ADEN);
}

ISR(ADC_vect) {
    uint16_t data = ADC;
    write_data(data);
}
