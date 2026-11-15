#include "ffta.h"

/* Target: [0x0800E878, 0x0800EA0C), 404 bytes, 197 instructions. */
typedef struct {
    u16 left;
    u16 right;
} CircleSpan;

extern u8 data_02009160;

void func_0800E878(s16 center_x, s16 center_y, u16 radius,
                   CircleSpan *spans, u8 clip, u8 side)
{
    s16 x, y;
    s16 error;
    u16 left, right;
    s16 row;

    if (radius == 0)
        return;

    x = 0;
    y = radius;
    error = 3 - 2 * radius;
    if (clip == 0) {
        center_y = 0;
        if (side == 0)
            center_y = radius;
    }

    while (x <= y) {
        left = center_x - x;
        right = center_x + x + data_02009160;
        if (side == 1) {
            row = center_y + y;
            if (row >= 0 && (clip == 0 || row < 160)) {
                spans[row].left = left;
                spans[row].right = right;
            }
        } else if (side == 0) {
            row = center_y - y;
            if (row >= 0 && (clip == 0 || row < 160)) {
                spans[row].left = left;
                spans[row].right = right;
            }
        }

        left = center_x - y;
        right = center_x + y + data_02009160;
        if (side == 1) {
            row = center_y + x;
            if (row >= 0 && (clip == 0 || row < 160)) {
                spans[row].left = left;
                spans[row].right = right;
            }
        } else if (side == 0) {
            row = center_y - x;
            if (row >= 0 && (clip == 0 || row < 160)) {
                spans[row].left = left;
                spans[row].right = right;
            }
        }

        if (error < 0) {
            error += 4 * x + 6;
        } else {
            error += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}
