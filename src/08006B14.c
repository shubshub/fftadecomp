#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u8 count;
    u8 current;
    u32 unknown_04;
    u32 *words;
    u8 *flags;
} State;

u8 func_08006B14(State *state, u32 value)
{
    u8 index;

    for (index = 0; index < state->count; index++) {
        if (state->words[index] == 0) {
            state->words[index] = value;
            state->flags[index] = 0;
            break;
        }
    }
    return index;
}
