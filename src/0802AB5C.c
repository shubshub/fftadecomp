#include "ffta.h"

typedef struct {
    u8 unknown_00[0x79];
    u8 value;
} State0802AB5C;

u8 func_0802AB5C(const State0802AB5C *state)
{
    return state->value;
}
