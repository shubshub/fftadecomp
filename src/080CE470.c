#include "ffta.h"

/* 0x080CE470..0x080CE476: 6 bytes, 3 instructions. */
typedef struct {
    u8 unknown_00[0xE3];
    u8 value;
} ObjectState;

void func_080CE470(ObjectState *state, u8 value)
{
    state->value = value;
}
