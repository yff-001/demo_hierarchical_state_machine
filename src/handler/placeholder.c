// #include "communication.h"

// #include "driver/gpio.h"
// #include "driver/timer.h"
// #include "driver/uart.h"

// #include "handler/communication.h"
// #include "handler/xtimer.h"
// #include "xtimer.h"

// #include <stdint.h>

// #define BUFFER_SIZE 255

// #define SYNC_BYTE           0x55
// #define START_BYTE          0x5C

// #define TIME_SETUP          3
// #define TIME_DISABLE_SYNC   5
// #define TIME_MESSAGE_LENGTH 10

// enum communication_state_t {
//     COMM_IDLE,
//     COMM_STEP_1,
//     COMM_STEP_2,
//     COMM_STEP_3,
//     COMM_STEP_4,
//     COMM_STEP_5,
//     COMM_STEP_6,
//     COMM_STEP_7
// };

// static enum communication_state_t last_state;
// static enum communication_state_t current_state;
// static enum communication_state_t next_state;

// volatile static uint8_t buffer_index = 0;

// /* variables used to flag events */
// volatile static uint8_t comm_device_detected = 0;
// static uint8_t count = 0;

// uint8_t message_buffer[BUFFER_SIZE] = {0};

// void rx_put(uint8_t data);

// void communication_init() {
//     uart0_init(&rx_put);

//     last_state = COMM_IDLE;
//     current_state = COMM_IDLE;
//     next_state = COMM_IDLE;
// }

// /*  a section performs actions similar to pon.c
//     for power plug detection, RX pin should be configured as INPUT
// */
// // void pon_task() {
// //     /* check the inverted VCOM level */
// //     uint16_t vcom_inverted = 0;

// //     /* set TX high (but why?) */

// //     for (;;) {
// //         //
// //     }

// //     /* set TX low (again why?) */

// //     vcom_inverted = vcom_inverted << 1;
// //     if (gpio_read_vcom()) {                      // look for a VCOM HIGH, thus reading RX LOW returns a 1 makes sense
// //         vcom_inverted |= 1;
// //     }
// // }

// /*  a section performs actions similar to com.c
//     for communication, RX is configured as UART initialization process
// */

// void communication_task() {
//     gpio_toggle_r();

//     do {
//         current_state = next_state;

//         switch (current_state) {
//             case COMM_IDLE:
//             /* UART0 power should be cut at this stage */
//             if (last_state != current_state) {
//                 /* this will never be reached */
//             }
//             else {
//                 if (1) {
//                     next_state = COMM_STEP_1;                                   // it is here to kickstart the sequence
//                 }
//             }
//             if (next_state != current_state) {

//             }
//             break;

//             case COMM_STEP_1:
//             // wait 30 ms, and enable serial
//             if (last_state != current_state) {
//                 count = TIME_SETUP;
//                 gpio_toggle_g();
//             }
//             else {
//                 if (--count == 0) {
//                     next_state = COMM_STEP_2;
//                 }
//             }
//             if (next_state != current_state) {
//                 gpio_toggle_g();
//             }
//             break;

//             case COMM_STEP_2:
//             // send sync byte (0x55), set up 20 ms timeout                      // if timeout, exit super-state
//             if (last_state != current_state) {
//                 uart0_send_byte(SYNC_BYTE);
//             }
//             else {
//                 next_state = COMM_STEP_3;
//             }
//             break;

//             case COMM_STEP_3:
//             // wait 50 ms
//             if (last_state != current_state) {
//                 count = TIME_DISABLE_SYNC;
//                 gpio_toggle_g();
//             }
//             else {
//                 if (--count == 0) {
//                     next_state = COMM_STEP_4;
//                 }
//             }
//             if (next_state != current_state) {
//                 gpio_toggle_g();
//             }
//             break;

//             case COMM_STEP_4:
//             /* disable UART0 on pin */
//             if (last_state != current_state) {
//                 uart0_disable();
//             }
//             else {
//                 next_state = COMM_STEP_5;
//             }
//             break;

//             case COMM_STEP_5:
//             // timeout of 100 ms
//             if (last_state != current_state) {                                  // entry
//                 count = TIME_MESSAGE_LENGTH;

//                 /* assume RX is already enabled and ready */



//                 gpio_toggle_g();
//             }
//             else {                                                              // internal
//                 if (--count == 0) {
//                     next_state = COMM_STEP_6;
//                 }
//                 if (comm_device_detected == 1) {

//                 }
//                 /*  length byte received
//                 */
//                 if (0) {
//                     next_state = COMM_STEP_6;
//                 }
//             }
//             if (next_state != current_state) {                                  // exit
//                 gpio_toggle_g();
//             }
//             break;

//             case COMM_STEP_6:
//             if (last_state != current_state) {
//                 count = 3 /* message byte - 2 */;
//                 gpio_toggle_g();
//             }
//             else {
//                 if (--count == 0) {
//                     next_state = COMM_STEP_7;
//                 }
//                 /*  entire message is received, counted in systicks, exit this state
//                     need uart0 driver to check this, probably
//                 */
//                 if (0) {
//                     //
//                 }
//             }
//             if (next_state != current_state) {
//                 gpio_toggle_g();
//             }
//             break;

//             case COMM_STEP_7:
//             break;

//             default:
//             break;
//         }

//         last_state = current_state;
//     } while (current_state != next_state);
// }

// void rx_put(uint8_t data) {
//     message_buffer[buffer_index] = data;
//     buffer_index++;

//     /* how do i check the contents of buffer in synchronization with fsm */
//     switch (0 /* check fsm state */) {
//     case COMM_STEP_5:                                                           // start byte is checked
//     if (message_buffer[0] == START_BYTE) {
//         comm_device_detected =1 ;
//     }
//     if (message_buffer[1] >= 5) {                                               // emits "E_COM_MESSAGE_LENGTH_DETECT" in old design, exit step 5
//         //
//     }
//     }
// }
