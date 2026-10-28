#include "ffta.h"

typedef struct {
    u16 left;
    u16 right;
} ScanlineSpan;

extern u8 data_02009160;
extern s32 func_08141870(s32 numerator, s32 denominator);
extern void func_0800E878(s32 center_x, s32 center_y, u16 radius,
                        ScanlineSpan *spans, u8 clip, u8 side);

static inline void fill_lower_ellipse(s32 center_x, s32 center_y,
                                     u16 radius, u16 half_radius,
                                     ScanlineSpan *spans, u8 clip)
{
    s16 y = 0;
    s32 scaled_x = 0;
    u16 previous_x = 0xFFFF;
    s16 x = radius;
    s16 error = x;

    while ((s16)x >= (s16)y) {
        s32 scaled_y;
        u16 left;
        u16 right;
        s16 row;

        if ((s16)x != (s16)previous_x) {
            scaled_x = func_08141870((s16)x * half_radius, radius);
            previous_x = x;
        }
        scaled_y = func_08141870((s16)y * half_radius, radius);
        left = center_x - (s16)x;
        right = center_x + (s16)x + data_02009160;
        row = center_y + scaled_y;
        if (row >= 0 && (clip == 0 || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }
        left = (s16)center_x - (s16)y;
        right = (s16)center_x + (s16)y + data_02009160;
        row = (s16)center_y + scaled_x;
        if (row >= 0 && (clip == 0 || row < 160)) {
            spans[row].left = left;
            spans[row].right = right;
        }
        error = (s16)error + 1 - 2 * (s16)y++;
        if ((s16)error < 0) {
            error = (s16)error + 2 * ((s16)x - 1);
            x--;
        }
    }
}

/* Complete target: [0x0800F068, 0x0800F308), 672 bytes. */
void func_0800F068(u16 center_x, u16 center_y, u16 radius,
                   ScanlineSpan *spans, u8 clip)
{
    if (radius == 0)
        return;
    func_0800E878((s16)center_x, (s16)center_y, radius, spans, clip, 0);
    if (clip == 0)
        fill_lower_ellipse((s16)center_x, (s16)center_y, radius,
                           radius >> 1, spans + radius, clip);
    else
        fill_lower_ellipse((s16)center_x, (s16)center_y, radius,
                           radius >> 1, spans, clip);
}
