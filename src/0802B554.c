#include "ffta.h"

typedef struct {
    u8 unknown_000[0x79A];
    u8 value;
} State0802B554;

/* 0802B554..0802B560: 01 4A 80 18 01 70 70 47 9A 07 00 00. */
void func_0802B554(State0802B554 *state, u8 value)
{
    state->value = value;
}
