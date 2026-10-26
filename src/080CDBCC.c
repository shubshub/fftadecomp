#include "ffta.h"

/* 0x080CDBCC..0x080CDBE4: 24 bytes. */
typedef struct {
    u8 unknown_00[0xEA];
    u8 flags;
} State;

u8 func_080CDBCC(const State *state)
{
    const u8 *flags = &state->flags;
    u8 mask = 8;

    mask &= *flags;
    if (mask == 0)
        return 0;
    return 1;
}
