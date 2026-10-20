#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0E];
    u16 flags;
} FlaggedObject;

void func_08020F80(FlaggedObject *object, u8 enabled)
{
    if (enabled)
        object->flags |= 2;
    else
        object->flags &= ~2;
}
