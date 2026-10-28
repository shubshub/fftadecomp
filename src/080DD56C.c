#include "ffta.h"

/* 0x080DD56C..0x080DD572: 6 bytes, 3 instructions. */
typedef struct {
    u8 unknown_00[0x28];
    s16 value;
} State;

s16 func_080DD56C(const State *state)
{
    return state->value;
}
