#include "ffta.h"

typedef struct {
    u32 flags;
    u8 unknown_04[0x24];
    u32 value;
} FlaggedValue;

u32 func_08021DA8(const FlaggedValue *object, u8 *first, u8 *second)
{
    u32 flags = object->flags;
    u32 result;

    if (flags & 0x40) {
        *first = ((flags & 8) != 0) ^ ((flags & 0x20) != 0);
        *second = (flags & 0x10) != 0;
        result = object->value;
    } else {
        result = 0;
    }

    return result;
}
