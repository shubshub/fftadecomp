#include "ffta.h"

typedef struct {
    u16 left;
    u16 right;
} CircleSpan;

extern u8 data_02009160;

/* Target: [0x0800E718, 0x0800E878), 352 bytes, 173 instructions. */
void func_0800E718(s16 center_x, s16 center_y, u16 radius,
                   CircleSpan *spans, u8 clip)
{
    s16 x;
    s16 y;
    u16 error;

    if (radius == 0)
        return;
    x = 0;
    y = radius;
    error = 3 - 2 * radius;
    if (clip == 0)
        center_y = y;
    for (; x <= y; x++) {
        s32 origin_x = center_x;
        s32 origin_y = center_y;
        u16 left = origin_x - x;
        u16 right = origin_x + x + data_02009160;
        s16 row = origin_y - -y;

        if (row >= 0 && (!clip || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }
        row = origin_y - y;
        if (row >= 0 && (!clip || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }
        left = origin_x - y;
        right = origin_x + y + data_02009160;
        row = origin_y - -x;
        if (row >= 0 && (!clip || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }
        row = origin_y - x;
        if (row >= 0 && (!clip || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }
        if ((s16)error < 0) {
            error = (s16)error + 6 + 4 * x;
        } else {
            error = (s16)error + 10 + 4 * (x - y);
            y = y - 1;
        }
    }
}
