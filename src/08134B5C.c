#include "ffta.h"

typedef struct {
    u8 priority;
    u8 unknown_01[15];
} PriorityRecord;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern BufferCopier const data_0836D4BC[];

/* 08134B5C..08134B88: 44 bytes. */
void func_08134B5C(PriorityRecord *destination, const PriorityRecord *source)
{
    if (source->priority == 0)
        return;
    if (destination->priority > source->priority)
        return;
    if (destination->priority == source->priority)
        return;

    data_0836D4BC[0](destination, source, sizeof(*destination));
}
