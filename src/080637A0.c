#include "ffta.h"

/* 0x080637A0..0x08063804: 100 bytes. */
typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[6];
    u16 mode;
    u8 unknown_50[4];
    u32 flags;
} CommandState;

extern CommandState *data_0200F450;

void func_080637A0(void)
{
    if (data_0200F450->mode == 0xBB || data_0200F450->mode == 0xCC)
        data_0200F450->flags |= 4;
    {
        CommandState *state = data_0200F450;

        state->flags |= 2;
        state->mode = 0xB7;
        state->current = 0x13;
        state->entries[state->count++] = state->current;
        state->current = 0x34;
        state->entries[state->count++] = state->current;
        state->current = 0x35;
    }
}
