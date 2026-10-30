#include "ffta.h"

typedef struct {
    u8 unknown_000[0x171];
    u8 value;
} State080BC9B8;

/* 0x080BC9B8..0x080BC9CC: 20 bytes, including alignment and the offset literal. */
u8 func_080BC9B8(State080BC9B8 *state)
{
    return state->value != 0;
}
