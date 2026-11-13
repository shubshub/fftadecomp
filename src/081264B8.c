#include "control_flags.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Owner081264B8;

typedef struct {
    Owner081264B8 *owner;
    u8 count;
    s8 direction;
    u8 level;
    u8 brightness;
} State081264B8;

typedef struct {
    u16 command;
    u16 unknown_02;
    Owner081264B8 *owner;
    u8 unknown_08[0xC];
    s16 direction;
    u16 count;
    u16 level;
} Request081264B8;

extern u16 data_0200F3D4[];
extern void func_08126430(State081264B8 *state);
extern void func_08007620(u16 *transition, u16 first, u16 second,
                          u16 target_first, u16 target_second);
extern u32 func_08007894(const void *state);
extern void func_080076F4(u16 *transition);
extern void func_08121E30(u8 level);

// Complete [0x081264B8, 0x081265B8): 256 bytes, 107 instructions.
u32 func_081264B8(void *unused, Request081264B8 *request, State081264B8 *state)
{
    u8 brightness;
    u8 target;

    switch (request->command) {
    case 0:
        state->owner = request->owner;
        state->direction = request->direction;
        state->count = request->count;
        state->level = request->level;
        func_08126430(state);
        break;
    case 0x100:
        if (state->count == 0) {
            request->command = 0x102;
            break;
        }
        brightness = state->brightness;
        target = ((100 - state->level) * 16) / 100;
        func_08007620(data_0200F3D4, brightness, 0, target, state->count);
        request->command = 0x101;
        break;
    case 0x101:
        if (func_08007894(data_0200F3D4)) {
            if (state->direction <= 0) {
                g_control_flags_03000940.bldy_lo =
                    ((100 - state->level) * 16) / 100;
                if (state->level == 100)
                    g_control_flags_03000940.bldcnt_lo = 0;
            }
            func_08121E30(state->level);
            request->command = 0x102;
            break;
        }
        func_080076F4(data_0200F3D4);
        g_control_flags_03000940.bldy_lo = data_0200F3D4[0];
        break;
    case 0x102:
        state->owner->complete = 1;
        request->command = 3;
        break;
    }
    return 0;
}
