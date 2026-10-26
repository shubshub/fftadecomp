#include "ffta.h"

/* 0x08096DE4..0x08096E16: 50 bytes. */
typedef struct {
    u8 unknown_00[0xD0];
    u32 flags;
} FlagState;

extern FlagState *data_0200F4A8;

void func_08096DE4(u8 enabled)
{
    FlagState *state = data_0200F4A8;

    if (enabled)
        state->flags &= ~0x2000;
    else
        state->flags |= 0x2000;
}
