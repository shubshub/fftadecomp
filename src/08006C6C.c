#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u8 count;
    u8 current;
    u32 unknown_04;
    u32 *words;
    u8 *flags;
} State;

void func_08006C6C(State *state, u8 flag)
{
    if (state->current != 0xFF) {
        state->flags[state->current] = flag;
    }
}
