#include "communication.h"
#include "../driver/uart.h"

#include <avr/boot.h>
#include <stdio.h>

#define Q_SIZE          8
#define RX_BUFFER_SIZE  255

/* a circular buffer for events */
struct q_t {
    uint8_t* buffer;
    uint8_t  head;
    uint8_t  tail;
};

volatile uint8_t rx_buffer_index;
volatile uint8_t rx_buffer_head;
volatile uint8_t rx_buffer_tail;
volatile uint8_t rx_buffer[Q_SIZE] = {0};

/*  comm_fsm() is the part taken out of main VS model, it is now systick driven
    set_action() is like any one in modules, fsm sets actions through this function
    rx_put() is the serial callback that pushes events to main VS model, now to comm_fsm()
    with this approach, actions and events are still needed to communicate with main fsm, thus
    setting up another fsm inside comm seems redundant
    an alternative to this approach is to program comm_fsm into main fsm as a concurrent region

    Vcom 001100 indicate a communication request, this should be handled by pon.c
*/

enum action_t {
    COMM_ACTION_IDLE,
    COMM_ACTION_ENABLE_TX,
    COMM_ACTION_ENABLE_RX,
    COMM_ACTION_DISABLE_TX,
    COMM_ACTION_DISABLE_RX,
    COMM_ACTION_SEND_SYNC,
    COMM_ACTION_EXECUTE_COMMAND,
    COMM_ACTOIN_SEND_REPLY
};

/* I'll call them signals because they are internal, but they are actually events previously */
enum signal_t {
    S_TRANSMISSION_COMPLETE,
    S_COMMUNICATION_DETECTED,
    S_EXECUTE_COMMAND_SUCCESS,
    S_EXECUTE_COMMAND_FAILURE
};

/* these are actually signals previously */
enum event_t {
    E_COMM_ENABLE,
    E_COMM_DISABLE
};

enum state_t {
    WAIT_SETUP_SEND,
    WAIT_SYNC_TX,
    WAIT_SETUP_COMMUNICATIOIN_PARTNER,
    WAIT_SETUP_RECEIVE,
    RECEIVE_COMM_CLIENT_DET,
    MESSAGE_LENGTH_BYTE,
    COMMAND_EXECUTION
};

enum state_t current_state = WAIT_SETUP_SEND;
enum event_t current_event = E_COMM_DISABLE;
enum action_t current_action = COMM_ACTION_IDLE;

static void comm_fsm();
static void set_action();
static uint8_t rx_put(uint8_t data);
static uint8_t q_is_available();
static uint8_t signal_is_available();

void communication_init() {
    uart0_init(&rx_put);
    // uart0_puts("hello world!\r\n");

    char fuse[16] = {0};
    sprintf(fuse, "ext.: %X\r\n", boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS));
    uart0_puts(fuse);

    sprintf(fuse, "high: %X\r\n", boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS));
    uart0_puts(fuse);

    sprintf(fuse, "low: %X\r\n", boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS));
    uart0_puts(fuse);
}

void communication_task() {
    while (signal_is_available()) {                         // make sure all signals are handled
        comm_fsm();
    }
}

static void comm_fsm() {
    /*  I have no choice but to run a while loop here, otherwise
        events will never be cleared as they are produced
        at a faster rate. RX interrupts could fire at 120/s
    */
    while (q_is_available()) {
        switch (current_state) {
            case WAIT_SETUP_SEND:
            switch (current_event) {
                case E_COMM_DISABLE:
                break;
            }
            break;
            case WAIT_SYNC_TX:
            break;
            default:
            break;
        }
    }
    // switch (current_state) {
    //     case WAIT_SETUP_SEND:
    //     switch (current_event) {
    //         case
    //     }
    //     break;
    //     case WAIT_SYNC_TX:
    //     break;
    //     default:
    //     break;
    // }
}

// static void set_action(enum action_t action) {
//     switch (action) {
//         case COMM_ACTION_IDLE:
//         break;
//         case COMM_ACTION_ENABLE_TX:
//         break;
//         case COMM_ACTION_EXECUTE_COMMAND:
//         /* execute command */
//         break;
//         default:
//         break;
//     }
// }

/*  This function is interrupt driven, comm fsm is systick driven
    thus they have to be decoupled
    signals are passed via a queue to facilitate cooperation
*/
static uint8_t rx_put(uint8_t data) {
    switch (data) {
        case SERIAL_CALLBACK_SEND_OK:
        switch (current_action) {
            case COMM_ACTION_SEND_SYNC:
            break;
        }
        break;
        case SERIAL_CALLBACK_RECEIVE_OK:
        break;
        case SERIAL_CALLBACK_RECEIVE_ERROR:
        break;
        case SERIAL_CALLBACK_CRC_ERROR:
        break;
        case SERIAL_CALLBACK_ERROR:
        break;
        default:
        break;
    }
}

static uint8_t q_is_available() {
    //
}

static uint8_t signal_is_available() {
    //
}
