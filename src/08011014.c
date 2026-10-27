#include "ffta.h"

struct State08011014 {
    u8 status;
    u8 unknown_01[0xB];
    u16 value;
    u16 counter;
    u16 elapsed;
};

void func_08011014(struct State08011014 *state, u16 value)
{
    state->value = value;
    state->counter = 0;
    state->elapsed = 0;
    if (state->status == 2)
        state->status = 1;
}
