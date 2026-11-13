#include "ffta.h"

// Target: complete [0x0800DFB0, 0x0800E05A), 170 bytes, 85 instructions.
// Fills the left edge of a span table along a line from (x0, y0) to
// (x1, y1); a horizontal line sets both edges of its one row.

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

struct Span0800DFB0 {
    u16 left;
    u16 right;
};

extern void func_080075CC(LineState *state, s32 x, s32 y, s32 endX, s32 endY);
extern void func_080076A0(LineState *state);
extern u32 func_08007880(const void *state);

void func_0800DFB0(u16 ax0, u16 ay0, u16 ax1, u16 ay1, struct Span0800DFB0 *spans)
{
    LineState line;
    s16 x0 = ax0;
    s16 y0 = ay0;
    s16 x1 = ax1;
    s16 y1 = ay1;
    s16 t;
    s16 y;

    if (y0 == y1) {
        if (y0 < 0 || y0 >= 160)
            return;
        if (x0 < x1) {
            spans[y0].left = x0;
            spans[y0].right = x1;
        } else {
            spans[y0].left = x1;
            spans[y0].right = x0;
        }
        return;
    }
    if (y0 >= y1) {
        t = x0;
        x0 = x1;
        x1 = t;
        t = y0;
        y0 = y1;
        y1 = t;
    }
    func_080075CC(&line, x0, y0, x1, y1);
    y = y0;
    while (!func_08007880(&line)) {
        if (y >= 160)
            break;
        if (y >= 0)
            spans[y].left = line.x;
        func_080076A0(&line);
        y++;
    }
}
