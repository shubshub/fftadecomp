#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0B];
    u8 value;
} ByteState;

void func_0813EF2C(ByteState *state, u8 value)
{
    state->value = value;
}
