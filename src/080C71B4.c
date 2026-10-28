#include "ffta.h"

/* 080C71B4 .. 080C7214: 96 bytes. */
typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 current;
    u8 pending;
    u16 x;
    u16 y;
    u8 unknown_08[0x40];
    u16 active;
    u8 unknown_4A[0x46];
} State;

extern State data_02015744;
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern u8 func_080C95A8(s32);

void func_080C71B4(u16 request)
{
    u8 value;
    State *state;

    if (!func_080C95A8(13))
        return;
    value = request;
    state = &data_02015744;
    if (state->current) {
        if (state->current == value)
            return;
        state->flags |= 4;
        state->pending = value;
    } else {
        g_callbacks_0836D4B8[0](state, sizeof(*state));
        state->current = value;
        state->x = 216;
        state->y = 152;
        if (value)
            state->active = 1;
    }
}
