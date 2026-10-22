/* 0x08007AD0 - 160 bytes
 * Target: 10b5041c2068a168401a000200146168e268891a0902091439f1bafe0004000e2169411a802903dd004807e000ffffff80204042814202da8020400009186069484364213af1d0fd011c206940182061002803da80214900401820612069ff2802dd0e4940182061207cfff791ff00040014a16941430912a0684018a060207cfff77cff00040014a16941430912e0684018e06010bc01bc0047000000ffffff
 */
#include "ffta.h"

typedef struct {
    s32 target_x;
    s32 target_y;
    s32 current_x;
    s32 current_y;
    s32 angle;
    s32 turn_percent;
    s32 speed;
} MotionState;

u16 func_08141860(s16 horizontal, s16 vertical);
s16 func_08007A60(u8 index);
s32 func_08007A4C(u8 index);

void func_08007AD0(MotionState *state)
{
    s32 difference = (func_08141860(
        (s16)((state->target_x - state->current_x) >> 8),
        (s16)((state->target_y - state->current_y) >> 8)) >> 8) - state->angle;

    if (difference > 128)
        difference -= 256;
    else if (difference < -128)
        difference += 256;

    difference = difference * state->turn_percent / 100;
    state->angle += difference;
    if (state->angle < 0)
        state->angle += 256;
    if (state->angle > 255)
        state->angle -= 256;

    state->current_x += (func_08007A60((u8)state->angle) * state->speed) >> 8;
    state->current_y += ((s16)func_08007A4C((u8)state->angle) * state->speed) >> 8;
}
