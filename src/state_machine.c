#include "state_machine.h"
#include "stateMachine.h"

#include "driver/uart.h"

enum event_t {E_VOID};

struct event_payload {
    char data;
    char* description;
};

/* hp: high power */
struct stateMachine sm_hp;

static void user_entry( void *stateData, struct event *event );
static void user_exit( void *stateData, struct event *event );
static void user_action( void *oldStateData, struct event *event, void *newStateData );
static bool user_guard( void *condition, struct event *event );
static void service_entry( void *stateData, struct event *event );
static void service_exit( void *stateData, struct event *event );
static void service_action( void *oldStateData, struct event *event, void *newStateData );
static bool service_guard( void *condition, struct event *event );
static void idle_entry( void *stateData, struct event *event );
static void idle_exit( void *stateData, struct event *event );
static void idle_action( void *oldStateData, struct event *event, void *newStateData );
static bool idle_guard( void *condition, struct event *event );
static void service_timeout_entry( void *stateData, struct event *event );
static void service_timeout_exit( void *stateData, struct event *event );
static void service_timeout_action( void *oldStateData, struct event *event, void *newStateData );
static bool service_timeout_guard( void *condition, struct event *event );

static struct state user, service, idle, motor_run, charge, service_timeout, motor_test, save_config, error;

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
//         .transitions = (struct transition[]) {E_VOID, (void *)(intptr_t)'0', &guard, &action, &service},
//         .numTransitions = 1,
//         },
//     [SERVICE] = {
//         .data = "service",
//         .entryAction = &entryAction,
//         .exitAction = &exitAction,
//         .transitions = (struct transition[]) {E_VOID, (void *)(intptr_t)'0', &guard, &action, &user},
//         .numTransitions = 1,
//         }
// };
/* EXPERIMENTAL */

static struct state user =
{
    .entryState = &idle,
    .data = "user",
    .entryAction = &user_entry,
    .exitAction = &user_exit,
    .transitions = (struct transition[]) {E_VOID, (void *)(intptr_t)'0', &user_guard, &user_action, &service},
    .numTransitions = 1,
};

static struct state service =
{
    .entryState = &service_timeout,
    .data = "service",
    .entryAction = &service_entry,
    .exitAction = &service_exit,
    .transitions = (struct transition[]) {E_VOID, (void *)(intptr_t)'0', &service_guard, &service_action, &user},
    .numTransitions = 1,
};

static struct state idle =
{
    .entryState = NULL,
    .data = "idle",
    .entryAction = &idle_entry,
    .exitAction = &idle_exit,
    .transitions = (struct transition[]) {
        {E_VOID, (void *)(intptr_t)'0', &idle_guard, &idle_action, &charge},
        {E_VOID, (void *)(intptr_t)'0', &idle_guard, &idle_action, &motor_run}
    },
    .numTransitions = 2,
};

static struct state service_timeout =
{
    .entryState = NULL,
    .data = "service timeout",
    .entryAction = &service_timeout_entry,
    .exitAction = &service_timeout_exit,
    .transitions = (struct transition[]) {
        {E_VOID, (void *)(intptr_t)'0', &service_timeout_guard, &service_timeout_action, &save_config},
        {E_VOID, (void *)(intptr_t)'0', &service_timeout_guard, &service_timeout_action, &motor_test}
    },
    .numTransitions = 2,
};

static struct state error =
{
    // .data = "Error",
    // .entryAction = &entryAction,
};

static void user_entry(void *stateData, struct event *event)
{
    uart0_puts("entry: ");
    uart0_puts((const char*)stateData);
    uart0_puts("\r\n");
}

static void user_exit(void *stateData, struct event *event)
{
    uart0_puts("exit: ");
    uart0_puts((const char*)stateData);
    uart0_puts("\r\n");
}

static void user_action(void *oldStateData, struct event *event, void *newStateData)
{
    uart0_puts("action: ");
    uart0_puts((const char*)oldStateData);
    uart0_puts(" -> ");
    uart0_puts((const char*)newStateData);
    uart0_puts("\r\n");
}

static bool user_guard(void *condition, struct event *event)
{
    /* cast the void pointer back to struct event_payload type */
    struct event_payload* event_data = (struct event_payload*)event->data;

    /* access the string literal with arrow operator */
    uart0_puts("guard: ");
    uart0_puts(event_data->description);
    uart0_puts("\r\n");

    return (intptr_t)condition == (intptr_t)event_data->data;
}

static void service_entry( void *stateData, struct event *event ) {
    //
}

static void service_exit( void *stateData, struct event *event ) {
    //
}

static void service_action( void *oldStateData, struct event *event, void *newStateData ) {
    //
}

static bool service_guard( void *condition, struct event *event ) {
    //
}

static void idle_entry( void *stateData, struct event *event ) {
    //
}

static void idle_exit( void *stateData, struct event *event ) {
    //
}

static void idle_action( void *oldStateData, struct event *event, void *newStateData ) {
    //
}

static bool idle_guard( void *condition, struct event *event ) {
    //
}

static void service_timeout_entry( void *stateData, struct event *event ) {
    //
}

static void service_timeout_exit( void *stateData, struct event *event ) {
    //
}

static void service_timeout_action( void *oldStateData, struct event *event, void *newStateData ) {
    //
}

static bool service_timeout_guard( void *condition, struct event *event ) {
    //
}

void state_machine_init()
{
    stateM_init(&sm_hp, &user, &error);

    /* events are dispatched here instead */

    struct event event_one = {E_VOID, &(struct event_payload){'0', "event one!"}};

    int res = stateM_handleEvent(&sm_hp, &event_one);
}

void state_machine_task()
{
    // struct event event_one = {E_VOID, &(struct event_payload){'0', "event one!"}};

    // int res = stateM_handleEvent(&sm_hp, &event_one);
}
