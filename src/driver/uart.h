#ifndef UART_H
#define UART_H

#include <stdint.h>

enum serial_status_t {
    SERIAL_CALLBACK_SEND_OK,
    SERIAL_CALLBACK_RECEIVE_OK,
    SERIAL_CALLBACK_RECEIVE_ERROR,
    SERIAL_CALLBACK_CRC_ERROR,
    SERIAL_CALLBACK_ERROR
};

void uart0_init(uint8_t (*callback)(uint8_t));
void uart0_transmit(uint8_t data);
void uart0_puts(const char* message);

// void uart1_init();
// void uart1_transmit(uint8_t data);
// void uart1_puts(char* message);

// void uart2_init();
// void uart2_transmit(uint8_t data);
// void uart2_puts(char* message);

// void uart3_init();
// void uart3_transmit(uint8_t data);
// void uart3_puts(char* message);

#endif
