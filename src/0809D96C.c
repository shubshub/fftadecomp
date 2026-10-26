#include "ffta.h"

typedef struct {
    const void *unit;
    u8 unknown_04[0xb0];
} Entry0809D96C;

typedef struct {
    u8 unknown_00[8];
    Entry0809D96C entries[13];
} Context0809D96C;

/* Complete [0x0809D96C, 0x0809D98C): 32 bytes, 16 instructions. */
s32 func_0809D96C(const Context0809D96C *context, const void *unit)
{
    s32 i = 0;
    const Entry0809D96C *entry = context->entries;

    for (; i < 13; entry++, i++) {
        if (entry->unit == unit)
            return 1;
    }
    return 0;
}
