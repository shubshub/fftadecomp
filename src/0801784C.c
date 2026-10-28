#include "ffta.h"

/* 0x0801784C..0x08017882: 54 bytes. */
typedef struct {
    u8 unknown_00[0x1A];
    s16 position;
} ScrollState;

extern u8 func_08017A90(ScrollState *state, u16 direction);

s16 func_0801784C(ScrollState *state, u16 direction)
{
    if (!func_08017A90(state, direction)) {
        return -1;
    }
    if (direction == 0x80) {
        state->position++;
    } else {
        state->position--;
    }
    return (u16)state->position * 2;
}
