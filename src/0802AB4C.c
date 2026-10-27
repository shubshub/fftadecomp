#include "ffta.h"

typedef struct {
    u8 unknown_00[0x80];
    u8 value;
} ValueState;

/* 0802AB4C..0802AB52: 6 bytes, 3 instructions. */
void func_0802AB4C(ValueState *state, u8 value)
{
    state->value = value;
}
