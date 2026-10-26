#include "ffta.h"

/* 0x080CDC2C..0x080CDC44: 24 bytes. */
typedef struct {
    u8 unknown_00[0xEC];
    u8 flags;
} State;

u8 func_080CDC2C(const State *state)
{
    const u8 *flags = &state->flags;
    u8 mask = 0x40;

    mask &= *flags;
    if (mask == 0)
        return 0;
    return 1;
}
