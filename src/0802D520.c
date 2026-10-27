#include "ffta.h"

/* 0x0802D520..0x0802D550: 48 bytes. */
typedef struct {
    u8 unknown_00[4];
    s16 x;
    s16 y;
    u8 unknown_08[8];
    u16 flags;
} PositionState;

void func_0802D520(PositionState *state)
{
    if (state->flags & 0x40) {
        state->x = 248;
    } else {
        state->x = -88;
    }
    if (state->flags & 0x80) {
        state->y = 120;
    } else {
        state->y = 24;
    }
}
