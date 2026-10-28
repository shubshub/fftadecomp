#include "ffta.h"

/* 0x08092230..0x08092288: 88 bytes, 39 instructions. */
typedef struct {
    u8 unknown_00[4];
    void *child;
    u8 unknown_08[0x40];
    u8 flags_a;
    u8 flags_b;
    u8 flags_c;
    u8 flags_d;
} SavedControls;

typedef struct {
    u8 unknown_00[0x4A];
    u8 flags_a;
    u8 flags_b;
    u8 flags_c;
    u8 flags_d;
} ControlFlags;

extern ControlFlags g_control_flags_03000940;
extern void func_08022854(void *object);

void func_08092230(SavedControls *state)
{
    if (state->child) {
        func_08022854(state->child);
    }
    g_control_flags_03000940.flags_a = state->flags_a;
    g_control_flags_03000940.flags_b = state->flags_b;
    g_control_flags_03000940.flags_c = state->flags_c;
    g_control_flags_03000940.flags_d = state->flags_d;
    func_08022854(state);
}
