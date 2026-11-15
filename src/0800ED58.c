#include "ffta.h"

/* Target: [0x0800ED58, 0x0800F068), 784 bytes, 370 instructions. */
/* Fills the scanline spans of an ellipse; equal radii go to the circle filler. */

typedef struct {
    u16 left;
    u16 right;
} CircleSpan;

extern u8 data_02009160;
extern s32 func_08141870(s32 numerator, s32 denominator);
extern void func_0800E878(s16 center_x, s16 center_y, u16 radius,
                          CircleSpan *spans, u8 clip, u8 side);

static inline void fill_wide_ellipse(s16 center_x, s16 center_y,
                                     u16 radius_x, u16 radius_y,
                                     CircleSpan *spans, u8 clip, u8 side)
{
    s16 y = 0;
    s32 scaled_x = 0;
    s16 previous_x = -1;
    s16 x = radius_x;
    s16 error = radius_x;

    while (x >= y) {
        s32 scaled_y;
        u16 left, right;
        s16 row;

        if (x != previous_x) {
            scaled_x = func_08141870(x * radius_y, radius_x);
            previous_x = x;
        }
        scaled_y = func_08141870(y * radius_y, radius_x);

        left = center_x - x;
        right = center_x + x + data_02009160;
        if (side == 1) {
            row = center_y + scaled_y;
            if (row >= 0 && (clip == 0 || row < 160)) {
                spans[row].left = left;
                spans[row].right = right;
            }
        } else if (side == 0) {
            row = center_y - scaled_y;
            if (row >= 0 && (clip == 0 || row < 160)) {
                spans[row].left = left;
                spans[row].right = right;
            }
        }

        left = center_x - y;
        right = center_x + y + data_02009160;
        if (side == 1) {
            row = center_y + scaled_x;
            if (row >= 0 && (clip == 0 || row < 160)) {
                spans[row].left = left;
                spans[row].right = right;
            }
        } else if (side == 0) {
            row = center_y - scaled_x;
            if (row >= 0 && (clip == 0 || row < 160)) {
                spans[row].left = left;
                spans[row].right = right;
            }
        }

        if ((error += 1 - 2 * y++) < 0)
            error += 2 * (x-- - 1);
    }
}

static inline void fill_tall_ellipse(s16 center_x, s16 center_y,
                                     u16 radius_x, u16 radius_y,
                                     CircleSpan *spans, u8 clip, u8 side)
{
    s16 x = 0;
    s32 scaled_y = 0;
    s16 previous_y = -1;
    s16 y = radius_y;
    s16 error = radius_y;

    while (y >= x) {
        s32 scaled_x;
        u16 left, right;
        s16 row;

        if (y != previous_y) {
            scaled_y = func_08141870(y * radius_x, radius_y);
            previous_y = y;
        }
        scaled_x = func_08141870(x * radius_x, radius_y);

        left = center_x - scaled_y;
        right = center_x + scaled_y + data_02009160;
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

        left = center_x - scaled_x;
        right = center_x + scaled_x + data_02009160;
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

        if ((error += 1 - 2 * x++) < 0)
            error += 2 * (y-- - 1);
    }
}

void func_0800ED58(s16 center_x, s16 center_y, u16 radius_x, u16 radius_y,
                   CircleSpan *spans, u8 clip, u8 side)
{
    if (radius_x == 0 || radius_y == 0)
        return;
    if (clip == 0) {
        if (side == 0)
            center_y = radius_y;
        else
            center_y = 0;
    }
    if (radius_x == radius_y)
        func_0800E878(center_x, center_y, radius_x, spans, clip, side);
    else if (radius_x > radius_y)
        fill_wide_ellipse(center_x, center_y, radius_x, radius_y,
                          spans, clip, side);
    else
        fill_tall_ellipse(center_x, center_y, radius_x, radius_y,
                          spans, clip, side);
}
