#include "event_queue.h"

#define BUFFER_SIZE  16

uint8_t event_queue[BUFFER_SIZE] = {0};
uint8_t event_queue_index = 0;
uint8_t event_queue_head = 0;
uint8_t event_queue_tail = 0;

uint8_t event_queue_available() {
    return (BUFFER_SIZE + event_queue_head - event_queue_tail) % BUFFER_SIZE;
}

uint8_t event_queue_get() {
    uint8_t ret = event_queue[event_queue_tail];
    event_queue_tail = (event_queue_tail + 1) % BUFFER_SIZE;
    return ret;
}

uint8_t event_queue_put(uint8_t value) {
    event_queue_index = (event_queue_index + 1) % BUFFER_SIZE;
    if (event_queue_index != event_queue_tail) {                        // if buffer is full, discard u
        event_queue[event_queue_head] = value;
        event_queue_head = event_queue_index;
    }
}