#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1E];
    u8 value;
} EncodedValue;

s32 func_08021C3C(const EncodedValue *object)
{
    if (object->value & 0x80)
        return object->value & ~0x80;

    return -1;
}
