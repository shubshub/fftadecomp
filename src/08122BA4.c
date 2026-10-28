#include "ffta.h"

/* Target: complete [0x08122BA4, 0x08122BC8), 36 bytes including literal. */
typedef struct {
    u8 unknown_00[7];
    u8 value;
} State08122BA4;

typedef struct {
    u8 unknown_00;
    u8 value;
} Input08122BA4;

extern u8 func_08122484(u8 value);

u32 func_08122BA4(State08122BA4 *state, const Input08122BA4 *input)
{
    state->value = input->value;
    if (func_08122484(state->value) == 0)
        return 0x110;
    return 0x113;
}
