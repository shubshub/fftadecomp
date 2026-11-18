#include "ffta.h"

typedef struct LineState {
    s32 x;
    s32 y;
    s32 endX;
    s32 endY;
    s32 stepX;
    s32 stepY;
    s32 deltaX;
    s32 deltaY;
    s32 accumulator;
    s32 error;
    s32 remaining;
} LineState;

typedef struct {
    u16 left;
    u16 right;
} ScanlineSpan;

extern u8 data_02009160;
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 endX, s32 endY);
extern void func_080076A0(LineState *state);

/* Complete [0x0800F770, 0x0800F860), 240 bytes. */
void func_0800F770(s16 x, s16 y, u16 radius, u16 height,
                   ScanlineSpan *spans, u8 clip)
{
    LineState line;
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

    func_080075CC(&line, radius, 0, 0, radius >> 1);
    for (i = 0; i < (radius >> 1); i++) {
        row = y + i;
        if (row >= 0 && (!clip || row < 160)) {
            spans[row].left = x - line.x;
            spans[row].right = x + line.x + data_02009160;
        }
        func_080076A0(&line);
    }
}
