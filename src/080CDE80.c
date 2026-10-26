#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} Object;

void func_080CDE80(Object *object, u8 enabled)
{
    u8 mask = 8;

    object->flags &= ~mask;
    if (enabled)
        object->flags |= mask;
}
