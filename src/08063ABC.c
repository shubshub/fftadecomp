#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[6];
    u16 field_4e;
    u8 unknown_50;
    u8 mode;
    u8 unknown_52[2];
    u32 flags;
    s32 first_argument;
    s32 second_argument;
} State08063ABC;

typedef struct {
    u8 unknown_0000[0x1f64];
    u32 resource;
} Resource08063ABC;

extern State08063ABC *data_0200F450;
extern u8 g_state_02000000[];

/* 0x08063ABC..0x08063B5C: 160 bytes, 71 instructions. */
void func_08063ABC(void)
{
    if (data_0200F450->second_argument == -1 ||
        data_0200F450->first_argument == -1) {
        State08063ABC *state;

        data_0200F450->field_4e = 0xc0;
        data_0200F450->mode = 0x10;
        if (data_0200F450->flags & 0x40) {
            Resource08063ABC *resources = (Resource08063ABC *)g_state_02000000;
            resources->resource += 5000;
            data_0200F450->flags &= ~0x40;
        }
        state = data_0200F450;
        state->count = 0;
        state->current = 0x30;
        state->entries[state->count++] = state->current;
        state->current = 0x39;
        state->entries[state->count++] = state->current;
        state->current = 0x3b;
        state->entries[state->count++] = state->current;
        state->current = 0x34;
        state->entries[state->count++] = state->current;
        state->current = 0x33;
    } else {
        data_0200F450->current = data_0200F450->entries[--data_0200F450->count];
    }
}
