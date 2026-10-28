#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2FBA];
    u8 coarse;
    u8 fine;
} CounterState;

extern CounterState g_state_02000000;

/* 0x08057C88..0x08057CBE: 54 bytes. */
void func_08057C88(void)
{
    CounterState *state = &g_state_02000000;
    if (state->fine <= 19) {
        state->fine++;
    } else {
        state->fine = 1;
        if (state->coarse <= 4)
            state->coarse++;
        else
            state->coarse = 1;
    }
}
