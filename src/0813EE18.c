#include "ffta.h"

/* 0x0813EE18..0x0813EE1E: 6 bytes. */
typedef struct {
    u8 unknown_00[0x8C];
    u8 value;
} State;

void func_0813EE18(State *state, u8 value)
{
    state->value = value;
}
