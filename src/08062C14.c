#include "ffta.h"

/* 0x08062C14..0x08062CA2: 142 bytes. */
typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[6];
    u16 mode;
    u8 marker;
    u8 unknown_51[0x0B];
    s32 selection;
} CommandState;

extern CommandState *data_0200F450;

void func_08062C14(void)
{
    if (data_0200F450->selection == -1) {
        CommandState *state;
        data_0200F450->mode = 0xAD;
        data_0200F450->marker = 3;
        state = data_0200F450;
        state->current = 0x2F;
        state->entries[state->count++] = state->current;
        state->current = 0x38;
    } else {
        CommandState *state;
        data_0200F450->mode = 0xB0;
        data_0200F450->marker = 3;
        state = data_0200F450;
        state->current = 0x0D;
        state->entries[state->count++] = state->current;
        state->current = 0x34;
        state->entries[state->count++] = state->current;
        state->current = 0x35;
        state->entries[state->count++] = state->current;
        state->current = 0x38;
    }
}
