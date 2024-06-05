#include "state_machine.h"
#include "stateMachine.h"

#include "driver/uart.h"

enum event_t {Event_dummy};

struct event_payload {
    char data;
    char* description;
};

struct stateMachine sm_device;

static void entryAction( void *stateData, struct event *event );
static void exitAction( void *stateData, struct event *event );
static void transAction( void *oldStateData, struct event *event, void *newStateData );
static bool guard( void *condition, struct event *event );

static struct state user, service, idle, run_motor, charge, error;

/* EXPERIMENTAL */
// enum state_t {
//     USER,
//     SERVICE,
//     IDLE,
//     MOTOR_ON,
//     CHARGE,
//     SERVICE_TIMEOUT,
//     MOTOR_TEST,
//     AUTO_SHELF,
//     SYSTEM_RESET
// };

// static struct state all_states[] = {
//     [USER] = {
//         .data = "user",
//         .entryAction = &entryAction,
//         .exitAction = &exitAction,
//         .transitions = (struct transition[]) {Event_dummy, (void *)(intptr_t)'0', &guard, &transAction, &service},
//         .numTransitions = 1,
//         },
//     [SERVICE] = {
//         .data = "service",
//         .entryAction = &entryAction,
//         .exitAction = &exitAction,
//         .transitions = (struct transition[]) {Event_dummy, (void *)(intptr_t)'0', &guard, &transAction, &user},
//         .numTransitions = 1,
//         }
// };
/* EXPERIMENTAL */

static struct state user =
{
    .data = "user",
    .entryAction = &entryAction,
    .exitAction = &exitAction,
    .transitions = (struct transition[]) {Event_dummy, (void *)(intptr_t)'0', &guard, &transAction, &service},
    .numTransitions = 1,
};

static struct state service =
{
    .data = "service",
    .entryAction = &entryAction,
    .exitAction = &exitAction,
    .transitions = (struct transition[]) {Event_dummy, (void *)(intptr_t)'0', &guard, &transAction, &user},
    .numTransitions = 1,
};

static struct state error =
{
    .data = "Error",
    .entryAction = &entryAction,
};

static void entryAction(void *stateData, struct event *event)
{
    uart0_puts("entry: ");
    uart0_puts((const char*)stateData);
    uart0_puts("\r\n");
}

static void exitAction(void *stateData, struct event *event)
{
    uart0_puts("exit: ");
    uart0_puts((const char*)stateData);
    uart0_puts("\r\n");
}

static void transAction(void *oldStateData, struct event *event, void *newStateData)
{
    uart0_puts("action: ");
    uart0_puts((const char*)oldStateData);
    uart0_puts(" -> ");
    uart0_puts((const char*)newStateData);
    uart0_puts("\r\n");
}

static bool guard(void *condition, struct event *event)
{
    /* cast the void pointer back to struct event_payload type */
    struct event_payload* event_data = (struct event_payload*)event->data;

    /* access the string literal with arrow operator */
    uart0_puts("guard: ");
    uart0_puts(event_data->description);
    uart0_puts("\r\n");

    return (intptr_t)condition == (intptr_t)event_data->data;
}

void state_machine_init()
{
    stateM_init(&sm_device, &user, &error);
}

void state_machine_task()
{
    struct event event_one = {Event_dummy, &(struct event_payload){'0', "event one!"}};

    int res = stateM_handleEvent(&sm_device, &event_one);
}
