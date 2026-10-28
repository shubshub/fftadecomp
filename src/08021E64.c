#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1D];
    u8 value;
} State08021E64;

void func_08021E64(State08021E64 *state, u8 value)
{
    state->value = value;
}
