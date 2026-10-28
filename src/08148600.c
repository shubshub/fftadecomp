#include "ffta.h"

/* 0x08148600..0x0814860A: 10 bytes, 5 instructions. */
typedef struct {
    u16 unknown_00;
    u16 flags;
} State;

void func_08148600(State *state)
{
    state->flags |= 8;
}
