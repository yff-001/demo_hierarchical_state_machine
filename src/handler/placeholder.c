#include "communication.h"

#include "driver/gpio.h"
#include "driver/timer.h"
#include "driver/uart.h"

#include "handler/communication.h"
#include "handler/xtimer.h"
#include "xtimer.h"

#include <stdint.h>

#define BUFFER_SIZE 255

#define TIME_SETUP          3
#define TIME_DISABLE_SYNC   5
#define TIME_MESSAGE_LENGTH 10

enum communication_state_t {
    COMM_IDLE,
    COMM_STEP_1,
    COMM_STEP_2,
    COMM_STEP_3,
    COMM_STEP_4,
    COMM_STEP_5,
    COMM_STEP_6,
    COMM_STEP_7
};

static enum communication_state_t last_state;
static enum communication_state_t current_state;
static enum communication_state_t next_state;

volatile static uint8_t buffer_index = 0;
static uint8_t count = 0;

void rx_put(uint8_t data);

void communication_init() {
    uart0_init(&rx_put);

    /*  thi set of values are used to simulate entering COMM_STEP_1 state
        from the get go
    */
    last_state = COMM_IDLE;
    current_state = COMM_STEP_1;
    next_state = COMM_STEP_1;
}

uint8_t message_buffer[BUFFER_SIZE] = {0};

/*  a section performs actions similar to pon.c
    for power plug detection, RX pin should be configured as INPUT
*/
// void pon_task() {
//     /* check the inverted VCOM level */
//     uint16_t vcom_inverted = 0;

//     /* set TX high (but why?) */

//     for (;;) {
//         //
//     }

//     /* set TX low (again why?) */

//     vcom_inverted = vcom_inverted << 1;
//     if (gpio_read_vcom()) {                      // look for a VCOM HIGH, thus reading RX LOW returns a 1 makes sense
//         vcom_inverted |= 1;
//     }
// }

/*  a section performs actions similar to com.c
    for communication, RX is configured as UART initialization process
*/

void communication_task() {
    gpio_toggle_r();

    do {
        current_state = next_state;

        switch (current_state) {
            case COMM_IDLE:
            /* UART0 power should be cut at this stage */
            break;

            case COMM_STEP_1:
            // wait 30 ms, and enable serial
            if (last_state != current_state) {
                count = TIME_SETUP;
                gpio_toggle_g();
            }
            else {
                if (--count == 0) {
                    next_state = COMM_STEP_2;
                }
            }
            if (next_state != current_state) {
                gpio_toggle_g();
            }

            break;

            case COMM_STEP_2:
            // send sync byte (0x55), set up 20 ms timeout              // if timeout, exit super-state
            if (last_state != current_state) {
                uart0_send_byte(0x55);
            }
            else {
                next_state = COMM_STEP_3;
            }

            break;

            case COMM_STEP_3:
            // wait 50 ms
            if (last_state != current_state) {
                count = TIME_DISABLE_SYNC;
                gpio_toggle_g();
            }
            else {
                if (--count == 0) {
                    next_state = COMM_STEP_4;
                }
            }
            if (next_state != current_state) {
                gpio_toggle_g();
            }
            break;

            case COMM_STEP_4:
            /* disable UART0 on pin */
            if (last_state != current_state) {
                uart0_disable();
            }
            else {
                next_state = COMM_STEP_5;
            }
            break;

            case COMM_STEP_5:
            // timeout of 100 ms
            if (last_state != current_state) {
                count = TIME_MESSAGE_LENGTH;
                gpio_toggle_g();
            }
            else {
                if (--count == 0) {
                    next_state = COMM_STEP_6;
                }
            }
            if (next_state != current_state) {
                gpio_toggle_g();
            }
            break;

            case COMM_STEP_6:
            break;

            case COMM_STEP_7:
            break;

            default:
            break;
        }

        last_state = current_state;
    } while (current_state != next_state);
}

void rx_put(uint8_t data) {
    // message_buffer[buffer_index] = data;
    // buffer_index++;


}
