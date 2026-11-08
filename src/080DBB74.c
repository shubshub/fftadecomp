#include "ffta.h"

typedef struct Task Task;

typedef struct {
    u16 message;
    u16 unknown_02;
    void *data;
    void *parameters;
    u32 unknown_0c;
    u32 unknown_10;
    u16 unknown_14;
    u16 unknown_16;
    u32 unknown_18;
} TaskEvent;

typedef struct {
    u32 value;
    u32 kind : 8;
    u32 index : 8;
    u32 field : 16;
} TaskPayload;

typedef struct {
    u32 first : 16;
    u32 second : 16;
    u32 third : 16;
    u32 delay : 16;
} TaskParameters;

extern s32 func_080DAE7C(Task *task, TaskEvent *event, void *data);
extern Task *func_08005B6C(s32 (*callback)(Task *, TaskEvent *, void *),
                           u16 size, TaskEvent *event, Task *parent);

Task *func_080DBB74(u32 value, u8 kind, u8 index, u16 first,
                    u16 second, u16 third, u16 delay, u32 unused, Task *parent)
{
    TaskEvent event;
    TaskPayload payload;
    TaskParameters parameters;

    payload.value = value;
    payload.kind = kind;
    payload.index = index;
    payload.field = 0;
    parameters.first = first;
    parameters.second = second;
    parameters.third = third;
    parameters.delay = delay;
    event.data = &payload;
    event.parameters = &parameters;
    return func_08005B6C(func_080DAE7C, 0x14, &event, parent);
}
