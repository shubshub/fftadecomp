#include "ffta.h"

typedef struct Motion080922CC {
    s32 target_x;
    s32 target_y;
    s32 current_x;
    s32 current_y;
    s32 angle;
    s32 unknown_14;
    s32 turn_percent;
    s16 offset_x;
    s16 offset_y;
    s32 unknown_20;
    s32 unknown_24;
} Motion080922CC;

extern void func_0801C918(s16 first, s16 second, s16 third, s16 *first_output,
                          s16 *second_output, s16 *third_output);
extern void func_0801E6F0(u16 *first, u16 *second);
extern u16 func_08141860(s16 horizontal, s16 vertical);

// Complete target [0x080922CC, 0x0809238E): 194 bytes.
void func_080922CC(Motion080922CC *state, s16 first, s16 second, s16 third,
                   s32 add_x, s32 add_y, s32 value_20, s32 value_14)
{
    s16 out[3];
    u16 view[2];
    s32 dx;
    s32 dy;
    s32 ax;
    s32 ay;
    s16 *out_y;
    u16 *view_x;
    u16 *view_y;

    ax = (s16)add_x;
    ay = (s16)add_y;
    func_0801C918(first, second, third, out, &out[1], &out[2]);
    state->target_x = (out[0] + ax) << 8;
    out_y = &out[1];
    state->target_y = (*out_y + ay) << 8;
    if (state->turn_percent == 0)
        state->turn_percent = 0x100;
    view_x = view;
    view_y = view + 1;
    func_0801E6F0(view_x, view_y);
    state->offset_x = *view_x;
    state->offset_y = *view_y;
    state->current_x = state->offset_x << 8;
    state->current_y = state->offset_y << 8;
    state->unknown_20 = value_20;
    state->unknown_14 = value_14;
    dx = state->target_x - state->current_x;
    if (dx < 0)
        dx = -dx;
    dy = state->target_y - state->current_y;
    if (dy < 0)
        dy = -dy;
    if (dx > dy)
        state->unknown_24 = dx;
    else
        state->unknown_24 = dy;
    state->angle = (u8)(func_08141860(dx >> 8, dy >> 8) >> 8);
    state->turn_percent = 0x100;
}
