#include "ffta.h"

typedef struct {
    u8 unknown_00[0x108];
} Entry0809A9F0;

typedef struct {
    u8 unknown_00[0x40];
    Entry0809A9F0 entries[2];
} Context0809A9F0;

/* Complete [0x0809A9F0, 0x0809AA10): 32 bytes, 16 instructions. */
u8 func_0809A9F0(Context0809A9F0 *context, const Entry0809A9F0 *entry)
{
    s32 i = 0;
    Entry0809A9F0 *current = context->entries;

    for (; i < 2; i++) {
        if (current == entry)
            return 1;
        current++;
    }
    return 0;
}
