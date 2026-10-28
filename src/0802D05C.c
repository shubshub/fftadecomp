#include "ffta.h"

struct State0802D05C {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    u8 unknown_0C[6];
    u8 flags;
    u8 width;
    u8 unknown_14[0x10];
    void *resource;
};

extern void func_08001CF0(void *resource, s16 x, s16 y, u32 first,
                          u32 second, u32 third, u32 fourth, u32 fifth,
                          u32 attributes, u32 sixth, u32 seventh);

/* Complete [0x0802D05C, 0x0802D0B0): 84 bytes, 41 instructions. */
void func_0802D05C(struct State0802D05C *state)
{
    s16 x = state->x;

    if (state->flags & 0x10)
        x -= state->width * 8;
    if (state->resource != 0)
        func_08001CF0(state->resource, x, state->y, 0,
                      0, 1, 1, 0, 0x240, 1, 0);
}
