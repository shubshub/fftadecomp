#include "ffta.h"

/* 0x08131204..0x0813121A: 22 bytes, 10 instructions. */
typedef struct {
    u32 unknown_00;
    u32 subject;
    u8 unknown_08[0x1C];
    u8 kind;
} State;

extern u32 func_0812D99C(u32 subject, u8 kind);

u8 func_08131204(const State *state)
{
    return func_0812D99C(state->subject, state->kind);
}
