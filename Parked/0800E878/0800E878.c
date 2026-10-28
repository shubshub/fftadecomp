#include "ffta.h"

/* 0x0800E878..0x0800EA0C: 404 bytes. */
typedef struct {
    u16 left;
    u16 right;
} CircleSpan;

extern u8 data_02009160;

void func_0800E878(u16 center_x, u16 center_y, u16 radius,
                   CircleSpan *spans, u8 clip, u8 side)
{
    s16 x, y;
    u16 error;
    u16 left, right;

    if (radius == 0)
        return;

    x = 0;
    y = radius;
    error = 3 - 2 * radius;
    if (clip == 0) {
        center_y = 0;
        if (side == 0)
            center_y = y;
    }

    while ((s16)x <= (s16)y) {
        s32 cx = (s16)center_x;
        s32 cy = (s16)center_y;
        left = cx - (s16)x;
        right = cx + (s16)x + data_02009160;
        if (side == 1) {
            u16 row = (s16)cy + (s16)y;
            if ((s16)row >= 0 && (clip == 0 || (s16)row < 160)) {
                spans[(s16)row].left = left;
                spans[(s16)row].right = right;
            }
        } else if (side == 0) {
            u16 row = (s16)cy - (s16)y;
            if ((s16)row >= 0 && (clip == 0 || (s16)row < 160)) {
                spans[(s16)row].left = left;
                spans[(s16)row].right = right;
            }
        }

        left = cx - (s16)y;
        right = cx + (s16)y + data_02009160;
        if (side == 1) {
            u16 row = (s16)cy + (s16)x;
            if ((s16)row >= 0 && (clip == 0 || (s16)row < 160)) {
                spans[(s16)row].left = left;
                spans[(s16)row].right = right;
            }
        } else if (side == 0) {
            u16 row = (s16)cy - (s16)x;
            if ((s16)row >= 0 && (clip == 0 || (s16)row < 160)) {
                spans[(s16)row].left = left;
                spans[(s16)row].right = right;
            }
        }

        if ((s16)error < 0) {
            error = (s16)error + 6 + 4 * (s16)x;
        } else {
            error = (s16)error + 10 + 4 * ((s16)x - (s16)y);
            y--;
        }
        x++;
    }
}
