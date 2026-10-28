#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} Object;

void func_080CDEEC(Object *object, u8 enabled)
{
    u8 mask = 0x40;

    object->flags &= ~mask;
    if (enabled)
        object->flags |= mask;
}
