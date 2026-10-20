#include "ffta.h"

typedef struct {
    u8 unknown_00[0x24];
    u32 flags;
} FlaggedObject;

void func_0809A260(void *context, u32 value)
{
    FlaggedObject *object = context;

    object->flags &= ~1u;
    if (value == 0)
        object->flags |= 1;
}
