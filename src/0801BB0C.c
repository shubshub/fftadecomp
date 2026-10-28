#include "ffta.h"

/* 0801BB0C..0801BB94: 136 bytes. */
struct Interpolation {
    u8 unknown_00[0x2C];
};

struct CameraState {
    u8 unknown_00[0x24];
    s16 x;
    s16 y;
    u8 unknown_28[0xC];
    u8 moving;
    u8 frame;
    s16 target_x;
    s16 target_y;
    u16 unknown_3A;
    struct Interpolation horizontal;
    struct Interpolation vertical;
};

extern struct CameraState g_state_02007F40;
extern void func_080075CC(struct Interpolation *interpolation,
                          s32 start, s32 offset, s32 end, s32 duration);

u16 func_0801BB0C(u16 x, u16 y, u16 duration)
{
    struct CameraState *state;

    if ((s16)x == g_state_02007F40.x && (s16)y == g_state_02007F40.y)
        return 0;

    state = &g_state_02007F40;
    state->target_x = x;
    state->target_y = y;
    func_080075CC(&state->horizontal, state->x, 0, (s16)x, duration - 1);
    func_080075CC(&state->vertical, state->y, 0, (s16)y, duration - 1);
    state->moving = 1;
    state->frame = 0;
    return duration;
}
