#include "ffta.h"

typedef struct {
    u32 value;
} WordRecord;

typedef struct {
    u8 unknown_00[0x1F];
    s8 value;
} ObjectState;

typedef struct {
    void *object;
    u8 unknown_04[4];
    s8 parameter;
    u8 unknown_09[9];
    u16 duration;
} ObjectRecord;

typedef struct {
    void *object;
    u8 *result;
    u8 mode;
    s8 event;
    s8 repeat_count;
    u8 delay;
    u16 initial_delay;
} EventDefinition;

typedef struct {
    u16 state;
    u16 unknown_2;
    const EventDefinition *definition;
} EventCommand;

typedef struct {
    void *object;
    u8 *result;
    u8 mode;
    s8 event;
    s8 repeat_count;
    u8 delay;
    u8 seen;
    u8 unknown_D;
    u16 timer;
} EventState;

typedef struct {
    EventCommand command;
    u32 unknown_08[5];
} EventRequest;

struct State080DD720;
typedef u32 (*TaskCallback)(void *, void *, void *);

extern u32 func_080DD47C(WordRecord *record);
extern void func_080DD720(struct State080DD720 *object, u32 mask);
extern void *func_080A880C(void *group);
extern void func_0809836C(void *object, u16 command, s8 value, u16 duration);
extern void *func_080DD350(void *object);
extern void func_080DE12C(void *object, u16 command, s8 value);
extern u32 func_080DDA94(void *task, EventCommand *command, EventState *state);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);

/* This dispatch also occurs in func_080DDF68, whose caller consumes duration. */
static inline void *send_object_command(void *group, u16 command, u16 *duration)
{
    void *object;

    *duration = 0;
    object = (void *)func_080DD47C(group);
    if (!(command & 0x4000))
        func_080DD720(object, 2);
    else
        command &= 0xBFFF;
    if (command & 0x8000) {
        ObjectRecord *record = func_080A880C(group);

        command &= 0x7FFF;
        func_0809836C(record->object, command, record->parameter, record->duration);
        *duration = record->duration;
    } else {
        ObjectState *state = func_080DD350(object);
        func_080DE12C(object, command, state->value);
    }
    return object;
}

/* The event constructor also has an out-of-line body at 080DE4B0. */
static inline void *start_event(void *object, u8 *result, u8 mode, s8 event,
                                s8 repeat_count, u8 delay, u16 initial_delay, void *parent)
{
    EventRequest request;
    EventDefinition definition;

    definition.object = object;
    definition.result = result;
    definition.mode = mode;
    definition.event = event;
    definition.repeat_count = repeat_count;
    definition.delay = delay;
    definition.initial_delay = initial_delay;
    request.command.definition = &definition;
    return func_08005B6C((TaskCallback)func_080DDA94, 0x10, &request, parent);
}

void *func_080DE524(void *group, void **out, u16 command, u8 *result, u8 mode,
                    u8 event, u8 repeat_count, u8 delay, u32 unused,
                    u16 initial_delay, void *parent)
{
    u16 duration;
    void *object = send_object_command(group, command, &duration);

    if (out)
        *out = object;
    return start_event(object, result, mode, event, repeat_count, delay, initial_delay, parent);
}
