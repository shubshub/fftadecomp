/* 0x080D993C: 48 bytes, including the scheduler callback literal. */
#include "ffta.h"

typedef struct TaskEvent {
    u16 state;
    u8 unknown_02[0x12];
    u16 first;
    u16 second;
    u16 third;
} TaskEvent;

typedef struct TaskPayload TaskPayload;
typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080D9528(void *task, TaskEvent *event, TaskPayload *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080D993C(u8 first, u8 second, u8 third, void *parent)
{
    TaskEvent descriptor;

    descriptor.first = first;
    descriptor.second = second;
    descriptor.third = third;
    return func_08005B6C((TaskCallback)func_080D9528, 12, &descriptor, parent);
}
