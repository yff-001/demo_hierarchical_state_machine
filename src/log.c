#include <stdio.h>
#include <stdarg.h>
#include "log.h"
#include "driver/timers.h"

log_level_t current_log_level = LOG_LEVEL_INFO;

void log_set_level(log_level_t level) {
    current_log_level = level;
}

void log_write(log_level_t level, const char *fmt, ...) {
    if (level > current_log_level) return;

    printf("[%lu] ", (unsigned long)timer_get_systick_accumulated());

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
