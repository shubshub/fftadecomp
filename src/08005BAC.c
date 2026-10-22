#include "ffta.h"

typedef struct TaskValue {
    u8 unknown_00[0x14];
    u16 value;
} TaskValue;

u16 func_08005BAC(const void *object)
{
    const TaskValue *task = (const TaskValue *)object;

    return task->value;
}
