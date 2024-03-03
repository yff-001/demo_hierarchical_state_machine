#include <avr/interrupt.h>
#include <avr/io.h>

#include "timers.h"

static volatile uint8_t systick_count_temp;
static volatile uint16_t permtick_count_temp;
static uint32_t systick_count;
static uint32_t systick_count_accumulated;
static uint32_t permtick_count;

/* systick runs at 100 Hz, implemented with Timer 0 */
void init_timer0() {
    TCCR0A |= (1 << WGM01);                     // CTC mode, OCRA0 as TOP
    TCCR0A |= (1 << CS00);
    TCCR0B |= (1 << CS02);
    TIMSK0 |= (1 << OCIE0A);
    OCR0A = 155;                                // 100.16 Hz
}

/* permtick runs at 1Hz, implemented with Timer 1 */
void init_timer1() {
    TCCR1B |= (1 << WGM12);                     // CTC mode, OCR1A as TOP
    TCCR1B |= (1 << CS10);                      // f=clk_io/1024
    TCCR1B |= (1 << CS12);
    TIMSK1 |= (1 << OCIE1A);                    // enable OUTPUT COMPARE A MATCH INTERRUPT
    OCR1A = 15624;                              // 1 Hz
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

/*  PHASE CORRECT PWM   */
void init_timer2() {
    // TODO
}

int has_timer0_ticked() {                   // I believe has_timer_ticked is much better than is_timer_pending
    if (systick_count_temp > 0) {
        return 1;
    }
    return 0;
}

void timer0_tick_count() {
    if (systick_count_temp > 0) {
        systick_count_temp--;
        systick_count++;
        systick_count_accumulated++;
    }
}

ISR(TIMER0_COMPA_vect) {
    systick_count_temp++;
}

ISR(TIMER1_COMPA_vect) {
    permtick_count_temp++;
}