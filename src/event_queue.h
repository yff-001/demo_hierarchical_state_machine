#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <stdint.h>

#define QUEUE_SIZE  16

int dequeue();
uint8_t enqueue(uint8_t value);
uint8_t is_queue_empty();
uint8_t is_queue_full();

#endif