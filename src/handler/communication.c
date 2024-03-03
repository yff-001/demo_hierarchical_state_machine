#include "communication.h"
#include "../driver/uart.h"

#define RX_BUFFER_SIZE  64

struct circular_buffer_t {
    uint8_t* buffer;
    uint8_t  head;
    uint8_t  tail;
};

volatile uint8_t rx_buffer[RX_BUFFER_SIZE] = {0};
volatile uint8_t rx_buffer_index;
volatile uint8_t rx_buffer_head;
volatile uint8_t rx_buffer_tail;