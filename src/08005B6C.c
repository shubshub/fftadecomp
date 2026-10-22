#include "ffta.h"

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct TaskScheduleManager {
    u8 unknown_00[0xC];
    u16 flags;
} TaskScheduleManager;

typedef struct TaskScheduleHeader {
    u8 unknown_00[0x16];
    u16 flags;
} TaskScheduleHeader;

void *func_08005954(void *manager, TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent)
{
    TaskScheduleManager **manager = (TaskScheduleManager **)0x02008FF0;
    TaskScheduleHeader *task = func_08005954(*manager, callback, payload_size,
                                           descriptor, parent);

    task->flags = (*manager)->flags ^ 1;
    return task;
}
