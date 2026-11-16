#include "ffta.h"

/* Target: complete [0x0800F6A8, 0x0800F770), 200 bytes, 96 instructions
 * and one literal word.
 * Fills the scanline spans of a diamond: a line from (radius_x, 0) to
 * (0, radius_y) gives the half-width of the rows above and below center_y. */

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

struct Span0800F6A8 {
    u16 left;
    u16 right;
};

extern u8 data_02009160;
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 endX, s32 endY);
extern void func_080076A0(LineState *state);

void func_0800F6A8(s16 center_x, s16 center_y, u16 radius_x, u16 radius_y,
                   struct Span0800F6A8 *spans, u8 clip)
{
    LineState line;
    s32 i;
    s16 row;

    if (radius_x == 0 || radius_y == 0)
        return;
    if (clip == 0)
        center_y = radius_y;

    func_080075CC(&line, radius_x, 0, 0, radius_y);
    for (i = 0; i < radius_y; i++) {
        row = center_y - i;
        if (row >= 0 && (clip == 0 || row < 160)) {
            spans[row].left = center_x - line.x;
            spans[row].right = center_x + line.x + data_02009160;
        }

        row = center_y + i;
        if (row >= 0 && (clip == 0 || row < 160)) {
            spans[row].left = center_x - line.x;
            spans[row].right = center_x + line.x + data_02009160;
        }

        func_080076A0(&line);
    }
}
