#ifndef TIMERS_H
#define TIMERS_H

void init_timer0();
void init_timer1();
void init_timer2();
void timer0_tick_count();
void timer1_tick_count();
int has_timer0_ticked();
int has_timer1_ticked();

#endif