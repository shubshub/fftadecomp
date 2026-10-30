#include "ffta.h"

typedef struct {
    u8 unknown_000[0x796];
    u8 value;
} State0802B59C;

/* 0x0802B59C..0x0802B5A8: 01 4A 80 18 01 70 70 47 96 07 00 00. */
void func_0802B59C(State0802B59C *state, u8 value)
{
    state->value = value;
}
