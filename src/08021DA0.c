#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u32 value;
} State08021DA0;

u32 func_08021DA0(State08021DA0 *state, u32 value)
{
    u32 previous = state->value;

    state->value = value;
    return previous;
}
