#ifndef TIMERS_H
#define TIMERS_H

void init_systick();
void init_permtick();
// void init_timer2();
void timer_systick_count();
void timer_permtick_count();
int has_systick_elapsed();
int has_permtick_elapsed();

#endif
