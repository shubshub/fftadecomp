#include "ffta.h"

typedef struct TaskManagerOwner {
    void *owner;
} TaskManagerOwner;

void *func_08007138(void *owner, u32 byte_count);

void *func_08005B28(u32 byte_count)
{
    TaskManagerOwner **manager = (TaskManagerOwner **)0x02008FF0;

    return func_08007138((*manager)->owner, byte_count);
}
