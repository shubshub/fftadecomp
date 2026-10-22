#include "ffta.h"

typedef struct TaskValue {
    u8 unknown_00[0x14];
    u16 value;
} TaskValue;

u32 func_08005BB0(const void *object)
{
    const TaskValue *task = object;

    return task->value == 2;
}
