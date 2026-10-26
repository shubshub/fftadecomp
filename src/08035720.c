#include "ffta.h"

struct SourceFlags {
    u8 first : 1;
    u8 unknown_01 : 4;
    u8 second : 1;
    u8 third : 1;
    u8 unknown_07 : 1;
} __attribute__((packed));

struct MenuContext {
    u8 unknown_000[4];
    struct SourceFlags *source;
    u8 unknown_008[0xF1C];
    u32 first;
    u32 control_a;
    u32 control_b;
    u32 second;
    u32 third;
};

struct ControlState {
    u8 unknown_00[0x9A];
    u8 first : 3;
    u8 unknown_03 : 5;
    u8 unknown_9B[0x4B];
    u8 second : 3;
    u8 unknown_07 : 5;
};

extern struct MenuContext *g_state_03002810;
extern struct ControlState data_030009E0;

/* Complete target: [0x08035720, 0x0803578C), 108 bytes. */
void func_08035720(void)
{
    struct MenuContext *state = g_state_03002810;

    state->first = state->source->first;
    state->control_a = data_030009E0.first;
    state->control_b = data_030009E0.second;
    state->second = state->source->second;
    state->third = state->source->third;
}
