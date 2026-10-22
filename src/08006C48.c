#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u8 count;
    u8 current;
    u32 unknown_04;
    u32 *words;
    u8 *flags;
} State;

void func_08006C48(State *state)
{
    if (state->current != 0xFF) {
        state->words[state->current] &= 0x7FFFFFFF;
    }
}
