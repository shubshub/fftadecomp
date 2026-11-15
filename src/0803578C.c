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
    u16 first : 3;
    u16 unknown_03 : 5;
    u8 unknown_9B[0x4B];
    u16 second : 3;
    u16 unknown_07 : 5;
};

extern struct MenuContext *g_state_03002810;
extern struct ControlState data_030009E0;

/* Complete target: [0x0803578C, 0x08035844), 184 bytes.
 * Writes back the five values func_08035720 (src/08035720.c) saved: the two
 * three-bit fields at data_030009E0 + 0x9A and + 0xE6 and the three one-bit
 * source flags. */
void func_0803578C(void)
{
    data_030009E0.first = g_state_03002810->control_a;
    data_030009E0.second = g_state_03002810->control_b;
    g_state_03002810->source->second = g_state_03002810->second;
    g_state_03002810->source->third = g_state_03002810->third;
    g_state_03002810->source->first = g_state_03002810->first;
}
