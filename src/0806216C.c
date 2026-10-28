#include "ffta.h"

/* 0x0806216C..0x08062224: 184 bytes. */
typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[5];
    u8 marker;
    u16 mode;
    u8 unknown_50[4];
    u32 flags;
} CommandState;

extern CommandState *data_0200F450;
extern u8 func_080C9540(u32 id);
extern void func_080C9574(u32 id, u32 active);

void func_0806216C(void)
{
    if (data_0200F450->flags & 8)
        data_0200F450->mode = 0xA6;
    else if (!func_080C9540(0x3F)) {
        data_0200F450->mode = 0xA4;
        func_080C9574(0x3F, 1);
    } else
        data_0200F450->mode = 0xA5;
    data_0200F450->flags |= 0x10;
    data_0200F450->flags |= 2;
    data_0200F450->marker = 1;
    if (data_0200F450->mode == 0xA6) {
        CommandState *state = data_0200F450;

        state->current = 2;
        state->entries[state->count++] = state->current;
        state->current = 0x31;
    } else
        data_0200F450->current = 3;
    {
        CommandState *state = data_0200F450;

        state->entries[state->count++] = state->current;
        state->current = 0x34;
        state->entries[state->count++] = state->current;
        state->current = 0x33;
    }
}
