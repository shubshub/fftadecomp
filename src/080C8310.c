#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} FlaggedObject;

u8 func_080C8310(const FlaggedObject *object)
{
    u8 result = 0;

    if (object != 0) {
        u16 flags = object->flags & 4;
        result = flags != 0;
    }

    return result;
}
