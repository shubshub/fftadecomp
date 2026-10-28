#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 mode;
    u8 unknown_05[5];
    u8 enabled;
} ModeState;

/* 08024ABC..08024AD6: 26 bytes, 13 instructions. */
void func_08024ABC(ModeState *state, u8 mode)
{
    state->mode = mode;
    if (mode == 0 || mode == 4)
        state->enabled = 1;
}
