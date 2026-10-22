#include "ffta.h"

typedef struct TaskValue {
    u8 unknown_00[0x14];
    u16 value;
} TaskValue;

void func_08005BA8(void *object, u16 value)
{
    TaskValue *task = (TaskValue *)object;

    task->value = value;
}
