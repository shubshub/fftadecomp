#include "ffta.h"

/* 0x080CDBB4..0x080CDBCC: 24 bytes. */
typedef struct {
    u8 unknown_00[0xEC];
    u8 flags;
} State;

u8 func_080CDBB4(const State *state)
{
    const u8 *flags = &state->flags;
    u8 mask = 1;

    mask &= *flags;
    if (mask == 0)
        return 0;
    return 1;
}
