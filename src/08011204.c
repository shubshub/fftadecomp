#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 flags;
} FlagState;

/* 08011204..0801121C: 24 bytes, 12 instructions. */
void func_08011204(FlagState *state)
{
    if (state->flags & 0x18)
        state->flags ^= 0x20;
}
