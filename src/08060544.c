#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1b];
    u8 count;
    u8 unknown_1c[4];
    const u8 *entries[0];
} State08060544;

extern State08060544 *data_0200F44C;

/* Complete [0x08060544, 0x0806057E): 58 bytes, 27 instructions. */
s16 func_08060544(void *unused, s16 index)
{
    const u8 *entry;
    s32 offset;

    if (index > 1)
        return 2;

    offset = index - 2;
    entry = data_0200F44C->entries[offset + data_0200F44C->count];
    if (!entry || !*entry)
        return -2;
    return index;
}
