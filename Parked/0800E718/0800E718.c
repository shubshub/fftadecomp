#include "ffta.h"

struct Span0800E718 {
    u16 left;
    u16 right;
};

extern u8 data_02009160;

/* Target: [0x0800E718, 0x0800E878), 352 bytes, 173 instructions. */
void func_0800E718(s16 center_x, s16 center_y, s16 radius,
                   struct Span0800E718 *spans, u8 clip)
{
    s16 x;
    s16 y;
    s16 error;

    if (radius == 0)
        return;
    x = 0;
    y = radius;
    error = 3 - 2 * y;
    if (clip == 0)
        center_y = y;
    for (; x <= y; x++) {
        u16 left = center_x - x;
        u16 right = center_x + x + data_02009160;
        s16 row = center_y + y;

        if (row >= 0 && (!clip || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }
        row = center_y - y;
        if (row >= 0 && (!clip || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }
        left = center_x - y;
        right = center_x + y + data_02009160;
        row = center_y + x;
        if (row >= 0 && (!clip || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }
        row = center_y - x;
        if (row >= 0 && (!clip || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }
        if (error < 0) {
            error += 6 + 4 * x;
        } else {
            error += 10 + 4 * (x - y);
            y--;
        }
    }
}
