#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE8];
    u8 flags;
} Object;

void func_080CDD40(Object *object, u8 enabled)
{
    u8 mask = 4;

    object->flags &= ~mask;
    if (enabled)
        object->flags |= mask;
}
