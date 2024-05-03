#include "state_machine.h"
#include "stateMachine.h"

enum event_t {Event_dummy};

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
    //
}

static void exitAction(void *stateData, struct event *event)
{
    //
}

static void transAction(void *oldStateData, struct event *event, void *newStateData)
{
    //
}

static bool guard(void *condition, struct event *event)
{
    //
}

void state_machine_init()
{
    stateM_init(&sm_device, &user, &error);
}

void state_machine_task()
{
    //
}
