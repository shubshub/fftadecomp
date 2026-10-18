#include "ffta.h"

typedef struct {
    u8 unknown_00[0x794];
    u16 fifth;
    u8 unknown_796;
    u8 first;
    u8 fourth;
    u8 unknown_799;
    u8 third;
    u8 second;
} State0802B048;

void func_0802B048(State0802B048 *state, u8 first, u8 second, u8 third,
                   u8 fourth, u16 fifth)
{
    state->first = first;
    state->second = second;
    state->third = third;
    state->fourth = fourth;
    state->fifth = fifth;
}
