#include "ffta.h"

typedef struct {
    u8 unknown_00[0x798];
    u8 value;
} ValueState;

/* 0802B56C..0802B576: 10 bytes, 5 instructions. */
void func_0802B56C(ValueState *state, u8 value)
{
    state->value = value;
}
