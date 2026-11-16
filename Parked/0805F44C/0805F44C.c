#include "ffta.h"

// Complete [0x0805F44C, 0x0805F4AC): 96 bytes, 48 instructions.
typedef struct Task05F44C Task05F44C;
typedef struct Scheduler05F44C Scheduler05F44C;

typedef struct Request05F44C {
    u8 unknown_00[20];
    u16 value;
    u16 slot;
    u8 unknown_18[4];
} Request05F44C;

typedef struct Context05F44C {
    Scheduler05F44C *scheduler;
    u32 unknown_04;
    Task05F44C *tasks[2];
    u8 flags[2];
} Context05F44C;

extern Context05F44C *data_0200F44C;

u32 func_0806094C(Task05F44C *task, Request05F44C *request, void *state);
Task05F44C *func_08005954(Scheduler05F44C *scheduler,
                          u32 (*callback)(Task05F44C *, Request05F44C *, void *),
                          u16 size, const Request05F44C *request,
                          Task05F44C *parent);

void func_0805F44C(u8 value)
{
    Request05F44C request;
    Context05F44C *context = data_0200F44C;
    u32 slot;

    if (context->tasks[0] == 0)
        slot = 0;
    else if (context->tasks[1] == 0)
        slot = 1;
    else
        for (;;)
            ;

    request.value = value;
    request.slot = slot;
    data_0200F44C->tasks[slot] = func_08005954(data_0200F44C->scheduler,
                                               func_0806094C, 0x98, &request, 0);
    data_0200F44C->flags[slot] = 0;
}
