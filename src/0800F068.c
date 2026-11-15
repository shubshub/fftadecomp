#include "ffta.h"

/* Target: [0x0800F068, 0x0800F308), 672 bytes, 317 instructions. */
/* Upper half circle via func_0800E878, then a lower half whose
   vertical radius is half the horizontal one. */

typedef struct {
    u16 left;
    u16 right;
} CircleSpan;

extern u8 data_02009160;
extern s32 func_08141870(s32 numerator, s32 denominator);
extern void func_0800E878(s16 center_x, s16 center_y, u16 radius,
                          CircleSpan *spans, u8 clip, u8 side);

static inline void fill_lower_half(s16 center_x, s16 center_y, u16 radius,
                                   u16 half_radius, CircleSpan *spans,
                                   u8 clip)
{
    s16 y = 0;
    s32 scaled_x = 0;
    s16 previous_x = -1;
    s16 x = radius;
    s16 error = radius;

    while (x >= y) {
        s32 scaled_y;
        u16 left, right;
        s16 row;

        if (x != previous_x) {
            scaled_x = func_08141870(x * half_radius, radius);
            previous_x = x;
        }
        scaled_y = func_08141870(y * half_radius, radius);

        left = center_x - x;
        right = center_x + x + data_02009160;
        row = center_y + scaled_y;
        if (row >= 0 && (clip == 0 || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }

        left = center_x - y;
        right = center_x + y + data_02009160;
        row = center_y + scaled_x;
        if (row >= 0 && (clip == 0 || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }

        if ((error += 1 - 2 * y++) < 0)
            error += 2 * (x-- - 1);
    }
}

void func_0800F068(s16 center_x, s16 center_y, u16 radius,
                   CircleSpan *spans, u8 clip)
{
    if (radius == 0)
        return;
    func_0800E878(center_x, center_y, radius, spans, clip, 0);
    if (clip == 0)
        fill_lower_half(center_x, center_y, radius, radius >> 1,
                        spans + radius, clip);
    else
        fill_lower_half(center_x, center_y, radius, radius >> 1,
                        spans, clip);
}
