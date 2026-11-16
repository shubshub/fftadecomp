#include "ffta.h"

typedef struct {
    u16 left;
    u16 right;
} Span0800F860;

extern u8 data_02009160;
void func_0800ED58(s16 x, s16 y, u16 horizontal, u16 vertical,
                   Span0800F860 *spans, u8 clip, u8 direction);

// Target: complete [0x0800F860, 0x0800F93A), 218 bytes, 105 instructions.
void func_0800F860(u16 x, u16 y, u16 radius, u16 height,
                   Span0800F860 *spans, u8 clip)
{
    u16 start;
    s16 row;
    s32 i;

    if (radius == 0)
        return;

    start = 0;
    if (clip == 0)
        y = height;
    else if (height == 0)
        height = y;
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
