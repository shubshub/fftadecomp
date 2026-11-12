#include "control_flags.h"

/* 080BCED0..080BD02C: 348 bytes. */
struct FadeState_080BCED0 {
    u8 unknown_000[0x1c9];
    u8 active;
    u8 unknown_1ca;
    u8 flags;
    u8 counter;
};

int func_080BCED0(struct FadeState_080BCED0 *state, u8 direction)
{
    if (direction) {
        if (!(state->flags & 2)) {
            state->flags = 2;
            g_control_flags_03000940.bldcnt_lo = 0x40;
            g_control_flags_03000940.bldcnt_hi = 0x3f;
            g_control_flags_03000940.bldalpha_lo = 0;
            g_control_flags_03000940.bldalpha_hi = 16;
            state->counter = 16;
            state->active = 1;
        } else {
            int count = state->counter - 1;
            state->counter = count;
            if ((u8)count) {
                g_control_flags_03000940.bldcnt_lo = 0;
                g_control_flags_03000940.bldcnt_hi = 0;
                state->flags = 0;
                state->active = 0;
                return 0;
            } else {
                g_control_flags_03000940.bldalpha_lo = 16 - count;
                g_control_flags_03000940.bldalpha_hi = count;
            }
        }
    } else {
        if (!(state->flags & 1)) {
            state->flags = 1;
            g_control_flags_03000940.bldcnt_lo = 0x40;
            g_control_flags_03000940.bldcnt_hi = 0x3f;
            g_control_flags_03000940.bldalpha_lo = 16;
            g_control_flags_03000940.bldalpha_hi = 0;
            state->counter = 16;
            state->active = 1;
        } else {
            int count = state->counter - 1;
            state->counter = count;
            if ((u8)count) {
                g_control_flags_03000940.bldcnt_lo = 0;
                g_control_flags_03000940.bldcnt_hi = 0;
                state->flags |= 4;
                state->active = 0;
                return 0;
            } else {
                g_control_flags_03000940.bldalpha_lo = count;
                g_control_flags_03000940.bldalpha_hi = 16 - count;
            }
        }
    }
    return 1;
}
