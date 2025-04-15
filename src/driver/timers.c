#include <avr/interrupt.h>
#include <avr/io.h>

#include "timers.h"

static volatile uint8_t systick_count_temp;
static volatile uint16_t permtick_count_temp;
static uint32_t systick_count;
static uint32_t permtick_count;
static uint32_t systick_count_accumulated;
static uint32_t permtick_count_accumulated;

/*
    systick runs at 100 Hz, implemented with Timer 2
    the main concern is that two output channels on timer 0 are side by side,
    thus timer 0 is more suitable for pwm output
    while timer 2 is more suitable for generating systick    
*/
void init_systick() {
    // TCCR0A |= (1 << WGM01);                     // CTC mode, OCRA0 as TOP
    // TCCR0A |= (1 << CS00);
    // TCCR0B |= (1 << CS02);
    // TIMSK0 |= (1 << OCIE0A);
    // OCR0A = 155;                                // 100.16 Hz

    TCCR2A |= (1 << WGM21);                     // CTC mode, OCRA as TOP
    TCCR2B |= (1 << CS20);
    TCCR2B |= (1 << CS21);
    TCCR2B |= (1 << CS22);
    TIMSK2 |= (1 << OCIE2A);
    OCR2A = 155;                                // 100.16 Hz
}

/* permtick runs at ~1Hz, implemented with watchdog timer on internal 128kHz oscillator */
void init_permtick() {
    // TCCR1B |= (1 << WGM12);                     // CTC mode, OCR1A as TOP
    // TCCR1B |= (1 << CS10);                      // f=clk_io/1024
    // TCCR1B |= (1 << CS12);
    // TIMSK1 |= (1 << OCIE1A);                    // enable OUTPUT COMPARE A MATCH INTERRUPT
    // OCR1A = 15624;                              // 1 Hz

    /*
        watchdog timer
        these lines have to be exact
        don't know why
    */
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = (1 << WDIE) | (1 << WDP2) | (1 << WDP1);
}

/* PHASE CORRECT PWM */
// void init_timer1() {
//     TCCR1A |= (1 << COM1A1);                    // clear on match when up-counting, set on match when down-counting
//     TCCR1A |= (1 << WGM10);                     // WGM1[3:0] = 0b1001
//     TCCR1B |= (1 << WGM12);                     // phase and frequency correct, OCR1A as TOP
//     TCCR1B |= (1 << CS10);                      // f=clk_io/64=250kHz
//     // TCCR1B |= (1 << CS11);
//     TIMSK1 |= (1 <<OCIE1A);                     // enable COMPARE MATCH A INTERRUPT
//     OCR1A = 127;                                //
// }

int has_systick_elapsed() {                   // I believe has_timer_ticked is much better than is_timer_pending
    if (systick_count_temp > 0) {
        return 1;
    }
    return 0;
}

int has_permtick_elapsed() {
    if (permtick_count_temp > 0) {
        return 1;
    }
    return 0;
}

void timer_systick_count() {
    if (systick_count_temp > 0) {
        systick_count_temp--;
        systick_count++;
        systick_count_accumulated++;
    }
}

void timer_permtick_count() {
    if (permtick_count_temp > 0) {
        permtick_count_temp--;
        permtick_count++;
        permtick_count_accumulated++;
    }
}

uint32_t timer_get_systick_accumulated(void) {
    return systick_count_accumulated;
}

ISR(TIMER2_COMPA_vect) {
    systick_count_temp++;
}

// ISR(TIMER1_COMPA_vect) {
//     permtick_count_temp++;
// }

ISR(WDT_vect) {
    permtick_count_temp++;
}
