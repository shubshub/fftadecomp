#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE];
    u16 extent;
    u8 unknown_10;
    u8 value;
} ScaledState;

/* Complete target: 0x0805872C..0x0805873C, 16 bytes. */
void func_0805872C(ScaledState *state, u8 value)
{
    state->value = value;
    state->extent = value * 40;
}
