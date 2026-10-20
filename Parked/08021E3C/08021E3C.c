#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    s16 value;
    s16 limit;
} BoundedValue;

s32 func_08021E3C(const BoundedValue *state)
{
    if (state->value < state->limit)
        return state->value;
    return state->value - 1;
}
