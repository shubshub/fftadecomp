#include "ffta.h"

/* Complete 0x08016D64..0x08016E1A: 182 bytes, 89 instructions. */
typedef struct {
    u8 unknown_00[0x12];
    u8 width;
    u8 height;
    u16 layout;
    u8 unknown_16[6];
    u8 flags;
    u8 unknown_1d[2];
    u8 mode;
    s16 end_x;
    s16 end_y;
    s16 start_x;
    s16 start_y;
    s16 step_x;
    s16 step_y;
} Transition;

void func_08016D64(Transition *transition)
{
    transition->flags &= ~4;
    transition->mode &= 0x7F;
    if (transition->mode == 0x10) {
        transition->end_x = transition->end_y = 0;
        transition->start_x = transition->start_y = 0;
    } else {
        u32 divisions;
        u32 layout;
        u32 fixed_width;
        u16 masked_layout;
        u8 width;
        u8 height;

        transition->end_x = transition->width;
        transition->end_y = transition->height;
        divisions = 4;
        layout = transition->layout;
        fixed_width = layout & 0x20;
        width = transition->width;
        height = transition->height;
        if (fixed_width)
            transition->step_x = divisions;
        else
            transition->step_x = (u8)(width / divisions);
        if (transition->step_x == 0)
            transition->step_x = 1;
        if (transition->mode & 1)
            transition->step_x += transition->step_x & 1;
        masked_layout = layout & 0x20;
        if (masked_layout || !(transition->mode & 1)) {
            transition->step_y = 1;
            transition->start_x = 0;
            transition->start_y = height;
        } else {
            transition->step_y = (u8)(height / divisions);
            if (transition->step_y == 0)
                transition->step_y = 1;
            transition->start_x = transition->start_y = 0;
        }
    }
}
