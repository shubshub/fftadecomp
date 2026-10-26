#include "ffta.h"

/* 0x0801B938..0x0801BA20: 232 bytes. */
typedef struct {
    s32 x;
    s32 y;
    s32 end_x;
    s32 end_y;
    s32 step_x;
    s32 step_y;
    s32 delta_x;
    s32 delta_y;
    s32 accumulator;
    s32 error;
    s32 remaining;
} LineState;

typedef struct {
    u8 unknown_00[0x24];
    s16 x;
    s16 y;
    u8 unknown_28[0x0C];
    u8 active;
    u8 frame;
    s16 target_x;
    s16 target_y;
    u16 speed;
    LineState horizontal;
    LineState vertical;
} MotionState;

extern MotionState g_state_02007F40;
extern u32 func_08141898(u32 value);
extern s32 func_08141870(s32 numerator, s32 denominator);
extern s32 func_08141874(s32 numerator, s32 denominator);
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 end_x, s32 end_y);

u16 func_0801B938(s16 x, s16 y)
{
    s16 dx, dy;
    u16 distance;
    u16 steps;

    if (x == g_state_02007F40.x && y == g_state_02007F40.y)
        return 0;

    dx = x - g_state_02007F40.x;
    dy = y - g_state_02007F40.y;
    distance = func_08141898((dx * dx + dy * dy) << 8);
    distance >>= 4;
    steps = func_08141870(distance, g_state_02007F40.speed);
    if (func_08141874(distance, g_state_02007F40.speed) != 0)
        steps++;

    g_state_02007F40.target_x = x;
    g_state_02007F40.target_y = y;
    func_080075CC(&g_state_02007F40.horizontal, g_state_02007F40.x, 0, x, steps - 1);
    func_080075CC(&g_state_02007F40.vertical, g_state_02007F40.y, 0, y, steps - 1);
    g_state_02007F40.active = 1;
    g_state_02007F40.frame = 0;
    return steps;
}
