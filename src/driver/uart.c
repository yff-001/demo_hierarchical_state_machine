/*
 * uart
 *
 * Interrupt driven TX & RX
 * Implemented with circular buffer
 *
 * Author: Yufeng Xu
 * Date: 2025-04-17
 */


#include <avr/interrupt.h>
#include <avr/io.h>

#include <stdio.h>

#include "uart.h"

#define TX_BUFFER_SIZE 64
#define RX_BUFFER_SIZE 64

#define BAUD_0      500000
#define UBRR_0      ((F_CPU)/(BAUD_0*8UL)-1)        // see spec sheet: buad rate generator

volatile uint8_t tx_buffer[TX_BUFFER_SIZE];
volatile uint8_t tx_head = 0;
volatile uint8_t tx_tail = 0;
volatile uint8_t tx_busy = 0;

volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
volatile uint8_t rx_head = 0;
volatile uint8_t rx_tail = 0;

uint8_t (*write_to_buffer)(uint8_t);

int uart_putchar(char c, FILE *stream);

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);


void uart0_init(uint8_t (*callback)(uint8_t)) {
    UBRR0L = (uint8_t)UBRR_0;                       // write lower byte
    UBRR0H = (uint8_t)(UBRR_0 >> 8);                // write higher byte

    UCSR0A |= (1<<U2X0);                            // U2X0 bit seems to be 1 by default on Pro Mini 3.3V 8Mhz
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);          // enable transmitter & receiver
    // UCSR0B |= (1 << RXCIE0);                        // enable RX Complete Interrupt
    UCSR0B = (1 << TXEN0)  | (1 << TXCIE0) | (1 << UDRIE0);

    stdout = &uart_stdout;
}

void uart0_register_callback(uint8_t (*callback)(uint8_t)) {
    write_to_buffer = callback;
}

/**
 * @brief Transmits a single byte over UART0.
 *
 * Waits until the UART0 transmit buffer is ready, then writes the data byte
 * to the UART0 data register for transmission.
 *
 * @param data The byte to be transmitted over UART0.
 */
void uart0_transmit(uint8_t data) {
    while (!(UCSR0A & (1<<UDRE0)));                 // wait for empty transmit buffer
    UDR0 = data;                                    // put data into buffer
}

void uart0_puts(const char* message) {
    while (*message) {
        uart0_transmit(*message++);
    }
}

// ISR(USART_RX_vect) {
//     uint8_t data = UDR0;
//     write_to_buffer(data);
// }

void uart_send_byte(uint8_t data) {
    uint8_t next_head = (tx_head + 1) % TX_BUFFER_SIZE;
    while (next_head == tx_tail); // Wait if buffer is full

    tx_buffer[tx_head] = data;
    tx_head = next_head;

    // Start transmission if not already transmitting
    if (!tx_busy) {
        tx_busy = 1;
        UCSR0B |= (1 << UDRIE0); // Enable Data Register Empty interrupt
    }
}


ISR(USART_UDRE_vect) {
    if (tx_tail != tx_head) {
        UDR0 = tx_buffer[tx_tail];
        tx_tail = (tx_tail + 1) % TX_BUFFER_SIZE;
    } else {
        // All data sent; disable interrupt
        UCSR0B &= ~(1 << UDRIE0);
        tx_busy = 0;
    }
}

ISR(USART_RX_vect) {
    uint8_t data = UDR0;
    uint8_t next_head = (rx_head + 1) % RX_BUFFER_SIZE;

    // Optional: Discard data if buffer is full
    if (next_head != rx_tail) {
        rx_buffer[rx_head] = data;
        rx_head = next_head;
    }
}


int uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_send_byte('\r'); // Convert LF to CRLF
    }
    uart_send_byte(c);
    return 0;
}
