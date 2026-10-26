#include "ffta.h"

/* 0x080CE458..0x080CE45E: 6 bytes, 3 instructions. */
typedef struct {
    u8 unknown_00[0xE0];
    u8 value;
} ObjectState;

void func_080CE458(ObjectState *state, u8 value)
{
    state->value = value;
}
