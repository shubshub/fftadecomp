#include "ffta.h"

/* 0x080CD9D4..0x080CD9EC: 24 bytes. */
typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} State;

u8 func_080CD9D4(const State *state)
{
    const u8 *flags = &state->flags;
    u8 mask = 0x20;

    mask &= *flags;
    if (mask == 0)
        return 0;
    return 1;
}
