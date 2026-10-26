#include "ffta.h"

/* 0x080CD974..0x080CD98C: 24 bytes, 12 instructions. */
typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} ObjectState;

u32 func_080CD974(const ObjectState *state)
{
    const u8 *flag_byte = &state->flags;
    u32 mask = 2;
    u32 flags = *flag_byte;

    if (!(flags & mask)) {
        return 0;
    }
    return 1;
}
