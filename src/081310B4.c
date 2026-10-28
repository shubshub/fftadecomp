#include "ffta.h"

/* 0x081310B4..0x081310CA: 22 bytes, 11 instructions. */
typedef struct {
    u8 unknown_00[0x26];
    u16 flags;
} State;

s32 func_081310B4(const State *state)
{
    if (!(state->flags & 1))
        return 0;
    return 100;
}
