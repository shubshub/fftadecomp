#include "ffta.h"

/* 0x080CDB3C..0x080CDB54: 24 bytes. */
typedef struct {
    u8 unknown_00[0xEB];
    u8 flags;
} State;

u8 func_080CDB3C(const State *state)
{
    const u8 *flags = &state->flags;
    u8 mask = 8;

    mask &= *flags;
    if (mask == 0)
        return 0;
    return 1;
}
