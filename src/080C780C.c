#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 current;
    u8 pending;
    u16 width;
    u16 height;
    u8 unknown_08[0x40];
    u16 enabled;
    u8 unknown_4A[0x46];
} DisplayState;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer const g_callbacks_0836D4B8[];

/* 080C780C..080C7858: 76 bytes. */
void func_080C780C(DisplayState *state, u8 value)
{
    if (state->current != 0) {
        if (state->current != value) {
            state->flags |= 4;
            state->pending = value;
        }
    } else {
        g_callbacks_0836D4B8[0](state, sizeof(*state));
        state->current = value;
        state->width = 216;
        state->height = 152;
        if (value != 0)
            state->enabled = 1;
    }
}
