#include "ffta.h"

typedef struct {
    u8 unknown_00[0xD0];
    u16 value;
} NestedState;

typedef struct {
    u8 unknown_00[8];
    NestedState *nested;
    u8 unknown_0C[0x1A];
    u16 flags;
} FlaggedState;

void func_08131DF0(FlaggedState *object)
{
    u16 flags = object->flags & 0x10;

    if (flags == 0)
        object->nested->value = 0;
}
