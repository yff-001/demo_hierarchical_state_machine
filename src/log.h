#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdint.h>

typedef enum {
    LOG_LEVEL_NONE = 0,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
} log_level_t;

extern log_level_t current_log_level;

void log_set_level(log_level_t level);
void log_write(log_level_t level, const char *fmt, ...);

// Macros for easy use
#define LOG_ERROR(...)  log_write(LOG_LEVEL_ERROR, "[ERROR] " __VA_ARGS__)
#define LOG_WARN(...)   log_write(LOG_LEVEL_WARN,  "[WARN] "  __VA_ARGS__)
#define LOG_INFO(...)   log_write(LOG_LEVEL_INFO,  "[INFO] "  __VA_ARGS__)
#define LOG_DEBUG(...)  log_write(LOG_LEVEL_DEBUG, "[DEBUG] " __VA_ARGS__)

#endif
