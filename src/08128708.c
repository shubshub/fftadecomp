#include "ffta.h"

typedef struct Motion08128708 {
    s32 target_x;
    s32 target_y;
    s32 current_x;
    s32 current_y;
    s32 angle;
    s32 turn_percent;
    s32 speed;
    s32 divisor;
    s32 span;
} Motion08128708;

extern s32 func_081426B8(s32 numerator, s32 denominator);
extern void func_08007AD0(Motion08128708 *state);
extern void func_0801E5E0(s16 x, s16 y);

/* Complete target [0x08128708, 0x081287C2), 186 bytes. */
u32 func_08128708(Motion08128708 *state)
{
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 near;
    s32 distance;
    s32 half;

    if (state->speed <= 0xFF)
        return 0;
    x = state->current_x >> 8;
    y = state->current_y >> 8;
    dx = state->target_x >> 8;
    dy = state->target_y >> 8;
    dx = x - dx;
    if (dx < 0)
        dx = -dx;
    if (dx <= 1) {
        near = y - dy;
        if (near < 0)
            near = -near;
        if (near <= 1)
            return 0;
    }

    dy = state->target_y - state->current_y;
    if (dy < 0)
        dy = -dy;
    dx = state->target_x - state->current_x;
    if (dx < 0)
        dx = -dx;
    distance = dy;
    if (dx > distance)
        distance = dx;

    half = state->span >> 1;
    if (half == 0) {
        state->speed = 0x100;
    } else if (half < distance) {
        if (state->divisor == 4)
            state->speed = func_081426B8(half - (distance - half), 4);
        else
            state->speed = func_081426B8(half, state->divisor);
        if (state->speed <= 0x1FF)
            state->speed = 0x200;
    } else {
        state->speed = func_081426B8(distance, state->divisor);
        if (state->speed <= 0xFF)
            state->speed = 0x100;
    }

    func_08007AD0(state);
    x = state->current_x >> 8;
    y = state->current_y >> 8;
    func_0801E5E0(x, y);
    return 1;
}
