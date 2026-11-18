#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    s32 remaining;
} LineState;

/* 0x08007AC4..0x08007AC8: 4 bytes. */
s32 func_08007AC4(const LineState *state)
{
    return state->remaining;
}
