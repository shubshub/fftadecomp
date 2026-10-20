#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE8];
    u8 flags;
} ObjectFlags;

u8 func_080CD92C(const ObjectFlags *object)
{
    if (!(object->flags & 0x40))
        return 0;
    return 1;
}
