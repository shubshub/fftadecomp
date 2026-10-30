#include "ffta.h"

typedef struct {
    u8 unknown_000[0x79C];
    u8 value;
} State0802B590;

/* 0x0802B590..0x0802B59C: 12 bytes, including the field-offset literal. */
void func_0802B590(State0802B590 *state, u8 value)
{
    state->value = value;
}
