#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 kind;
} KindState;

/* 0800C148..0800C15A: 18 bytes, 9 instructions. */
u8 func_0800C148(const KindState *state)
{
    return state->kind == 1;
}
