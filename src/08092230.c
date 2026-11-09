#include "control_flags.h"

/* 0x08092230..0x08092288: 88 bytes, 39 instructions. */
typedef struct {
    u8 unknown_00[4];
    void *child;
    u8 unknown_08[0x40];
    u8 bldcnt_lo;
    u8 bldcnt_hi;
    u8 bldalpha_lo;
    u8 bldalpha_hi;
} SavedControls;

extern void func_08022854(void *object);

void func_08092230(SavedControls *state)
{
    if (state->child) {
        func_08022854(state->child);
    }
    g_control_flags_03000940.bldcnt_lo = state->bldcnt_lo;
    g_control_flags_03000940.bldcnt_hi = state->bldcnt_hi;
    g_control_flags_03000940.bldalpha_lo = state->bldalpha_lo;
    g_control_flags_03000940.bldalpha_hi = state->bldalpha_hi;
    func_08022854(state);
}
