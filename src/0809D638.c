#include "ffta.h"

typedef struct {
    u8 unknown_00[0x26];
    u8 value;
} ByteState;

/* 0x0809D638..0x0809D63E: 6 bytes. */
void func_0809D638(ByteState *state, u8 value)
{
    state->value = value;
}
