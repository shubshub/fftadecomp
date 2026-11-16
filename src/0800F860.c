#include "ffta.h"

/* Target: complete [0x0800F860, 0x0800F93A), 218 bytes, 105 instructions. */

typedef struct {
    u16 left;
    u16 right;
} CircleSpan;

extern u8 data_02009160;
extern void func_0800ED58(s16 center_x, s16 center_y, u16 radius_x,
                          u16 radius_y, CircleSpan *spans, u8 clip, u8 side);

void func_0800F860(u16 x, u16 y, u16 radius, u16 height,
                   CircleSpan *spans, u8 clip)
{
    u16 start;
    s16 row;
    s32 i;

    if (radius == 0)
        return;

    /* Both clip arms leave start + height == y.  start is 0 in the second,
     * but `height = y;` there reorders the hoists at 0x0800F89E-0x0800F8A8
     * and turns the loop-entry beq at 0x0800F8AC into ble. */
    start = 0;
    if (clip == 0)
        y = height;
    else if (height == 0)
        height = y - start;
    else
        start = y - height;

    row = start;
    for (i = 0; i < height; i++) {
        if (row >= 0 && (!clip || row < 160)) {
            spans[row + i].left = x - radius;
            spans[row + i].right = radius + x + data_02009160;
        }
    }

    if (clip == 0)
        func_0800ED58(x, y, radius, radius >> 1, spans + height, clip, 1);
    else
        func_0800ED58(x, y, radius, radius >> 1, spans, clip, 1);
}
