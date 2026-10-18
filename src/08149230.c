#include "ffta.h"

typedef struct {
    u8 unknown_00[0x981];
    u8 first;
    u8 second;
    u8 third;
    u8 unknown_984[2];
    u8 fourth;
    u8 fifth;
} State08149230;

void func_08149230(State08149230 *state, u8 first, u8 second, u8 third,
                   u8 fourth, u8 fifth)
{
    state->first = first;
    state->second = second;
    state->third = third;
    state->fourth = fourth;
    state->fifth = fifth;
}
