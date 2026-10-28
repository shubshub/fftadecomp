#include "ffta.h"

/* 0x08045CF8..0x08045D90: 152 bytes. */
typedef struct {
    u8 id;
    u8 unknown_01[0x23];
    u16 flags;
    u8 unknown_26[0xE2];
} Unit;

typedef struct {
    u8 unknown_00[0x84];
    Unit units[24];
} GameState;

extern GameState g_state_02000000;

s32 func_08045CF8(u8 *output, s32 *selected, s32 *special)
{
    s32 count = 0;
    s32 i;
    GameState *state;

    *special = -1;
    i = 0;
    state = &g_state_02000000;
    for (; i < 24; ++i) {
        if (!(state->units[i].flags & 0x18)) {
            if (state->units[i].flags & 0x80) {
                if (state->units[i].flags & 0x400) {
                    *selected = i;
                    state->units[i].flags &= ~0x400;
                }
                output[count] = i;
                ++count;
                if (state->units[i].id == 2 || state->units[i].id == 15)
                    *special = i;
            }
        }
        state->units[i].flags &= ~0x80;
    }
    return count;
}
