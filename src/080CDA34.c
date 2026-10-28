#include "ffta.h"

/* 0x080CDA34..0x080CDA4C: 24 bytes. */
typedef struct {
    u8 unknown_00[0xEC];
    u8 flags;
} State;

u8 func_080CDA34(const State *state)
{
    u8 mask = 4;

    mask &= state->flags;
    if (mask == 0)
        return 0;
    return 1;
}
