#include "ffta.h"

/* 0x080CDD04..0x080CDD1C: 24 bytes. */
typedef struct {
    u8 unknown_00[0xED];
    u8 flags;
} State;

u8 func_080CDD04(const State *state)
{
    const u8 *flags = &state->flags;
    u8 mask = 0x80;

    mask &= *flags;
    if (mask == 0)
        return 0;
    return 1;
}
