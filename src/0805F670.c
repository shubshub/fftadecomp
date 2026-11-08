#include "ffta.h"

/* 0805F670: complete 44-byte owner, including its referenced literals. */
typedef struct Task05F670 Task05F670;
typedef struct Scheduler05F670 Scheduler05F670;

typedef struct Request05F670 {
    u16 event;
    u16 unknown_02;
    void *object;
    u8 unknown_08[20];
} Request05F670;

typedef struct SchedulerOwner05F670 {
    Scheduler05F670 *scheduler;
} SchedulerOwner05F670;

extern SchedulerOwner05F670 *data_0200F44C;

u32 func_08060E30(Task05F670 *task, Request05F670 *request, void *state);
Task05F670 *func_08005954(Scheduler05F670 *scheduler,
                        u32 (*callback)(Task05F670 *, Request05F670 *, void *),
                        u16 size, const Request05F670 *request,
                        Task05F670 *parent);

Task05F670 *func_0805F670(void *object)
{
    Request05F670 request;

    request.object = object;
    return func_08005954(data_0200F44C->scheduler, func_08060E30,
                         0x1098, &request, 0);
}
