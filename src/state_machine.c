#include "state_machine.h"
#include "stateMachine.h"

#include "driver/uart.h"

enum event_t {Event_dummy};

struct event_payload {
    char* data; 
};

struct stateMachine sm_device;

static void entryAction( void *stateData, struct event *event );
static void exitAction( void *stateData, struct event *event );
static void transAction( void *oldStateData, struct event *event, void *newStateData );
static bool guard( void *condition, struct event *event );

static struct state user, service, idle, run_motor, charge, error;

static struct state user =
{
    .data = "user",
    .entryAction = &entryAction,
    .exitAction = &exitAction,
    .transitions = (struct transition[]) {Event_dummy, (void *)'a', &guard, &transAction, &service},
    .numTransitions = 1,
};

static struct state service =
{
    .data = "user",
    .entryAction = &entryAction,
    .exitAction = &exitAction,
    .transitions = (struct transition[]) {Event_dummy, (void *)'a', &guard, &transAction, &user},
    .numTransitions = 1,
};

static struct state error =
{
    .data = "Error",
    .entryAction = &entryAction,
};

static void entryAction(void *stateData, struct event *event)
{
    uart0_puts(event->data);
    uart0_puts("entry\r\n");
}

static void exitAction(void *stateData, struct event *event)
{
    uart0_puts(event->data);
    uart0_puts("exit\r\n");
}

static void transAction(void *oldStateData, struct event *event, void *newStateData)
{
    uart0_puts(event->data);
    uart0_puts("action\r\n");
}

static bool guard(void *condition, struct event *event)
{
    uart0_puts("guard\r\n");
    /* cast the void pointer back to struct event_payload type */
    struct event_payload* event_data = (struct event_payload*)event->data;
    /* access the string literal with arrow operator */
    uart0_puts(event_data->data);
}

void state_machine_init()
{
    stateM_init(&sm_device, &user, &error);
}

void state_machine_task()
{
    struct event event_one = {Event_dummy, &(struct event_payload){"event one!"}};

    int res = stateM_handleEvent(&sm_device, &event_one);
}
