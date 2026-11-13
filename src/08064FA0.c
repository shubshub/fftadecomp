#include "ffta.h"

// 08064FA0: complete 136-byte owner [0x08064FA0, 0x08065028), including its
// referenced literals.  Builds a 0x1C-byte request whose halfword at +0x14 is
// the kind, then starts the task matching that kind under the shared manager.

typedef struct Task064FA0 Task064FA0;
typedef struct Scheduler064FA0 Scheduler064FA0;

typedef struct Request064FA0 {
    u8 unknown_00[0x14];
    u16 kind;
    u8 unknown_16[6];
} Request064FA0;

typedef struct SchedulerOwner064FA0 {
    Scheduler064FA0 *scheduler;
} SchedulerOwner064FA0;

extern SchedulerOwner064FA0 *data_0200F454;

u32 func_080651FC(Task064FA0 *task, Request064FA0 *request, void *state);
u32 func_08065608(Task064FA0 *task, Request064FA0 *request, void *state);
u32 func_080659AC(Task064FA0 *task, Request064FA0 *request, void *state);
u32 func_08065B58(Task064FA0 *task, Request064FA0 *request, void *state);
Task064FA0 *func_08005954(Scheduler064FA0 *scheduler,
                          u32 (*callback)(Task064FA0 *, Request064FA0 *, void *),
                          u16 size, const Request064FA0 *request,
                          Task064FA0 *parent);

Task064FA0 *func_08064FA0(u8 kind)
{
    Request064FA0 request;

    request.kind = kind;
    switch (kind) {
    case 9:
    case 10:
        return func_08005954(data_0200F454->scheduler, func_080659AC,
                             0x34, &request, 0);
    case 11:
        return func_08005954(data_0200F454->scheduler, func_08065B58,
                             0x10, &request, 0);
    case 4:
        return func_08005954(data_0200F454->scheduler, func_08065608,
                             0xDC, &request, 0);
    default:
        return func_08005954(data_0200F454->scheduler, func_080651FC,
                             0xDC, &request, 0);
    }
}
