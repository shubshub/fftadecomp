#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} ObjectFlags;

u8 func_080CD9A4(const ObjectFlags *object)
{
    u8 flags = object->flags;

    if (!(flags & 0x08))
        return 0;
    return 1;
}
