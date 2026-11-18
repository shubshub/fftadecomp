#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    s16 remaining;
} TransitionState;

/* 0x08007AC8..0x08007ACE: 6 bytes. */
s16 func_08007AC8(const TransitionState *state)
{
    return state->remaining;
}
