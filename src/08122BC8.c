#include "ffta.h"

/* Target: complete [0x08122BC8, 0x08122BEC), 36 bytes including literal. */
typedef struct {
    u8 unknown_00[7];
    u8 selection;
} State08122BC8;

extern u8 func_08122484(u8);

u32 func_08122BC8(State08122BC8 *state)
{
    state->selection = 255;
    if (func_08122484(state->selection) == 0)
        return 272;
    return 275;
}
