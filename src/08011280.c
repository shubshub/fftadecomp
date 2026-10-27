#include "ffta.h"

/* 0x08011280 - 36 bytes. Set or clear bit 6 of the state flags. */
typedef struct {
    u8 unknown_00[0x14];
    u16 flags;
} State08011280;

void func_08011280(State08011280 *state, u8 enabled)
{
    if (enabled)
        state->flags |= 0x40;
    else
        state->flags &= ~0x40;
}
