#include "ffta.h"

// Complete [0x08115A1C, 0x08115ACC): 176 bytes.
// Takes a third of the 0801CAE0 bounds as a position, then pulls y up when
// the 8-pixel rows below it (out of 160, less offset) exceed the row limit.

extern void func_0801CAE0(s16 *out);
extern s32 func_08141870(s32 numerator, s32 denominator);

void func_08115A1C(u32 unused, u16 offset, u16 rows, s16 *x_out, s16 *y_out)
{
    s16 bounds[6];
    s16 x;
    s16 y;
    u16 third;
    u16 limit;
    s16 bottom;
    s32 edge;

    func_0801CAE0(bounds);
    x = func_08141870((u16)bounds[4] >> 1, 3);
    y = func_08141870((u16)bounds[5] >> 1, 3);
    third = func_08141870((u16)bounds[5], 3);
    limit = third >> 3;
    if (third & 7)
        limit++;
    if (rows < limit) {
        edge = y + (0xA0 - (s16)offset);
        bottom = edge >> 3;
        if (edge & 7)
            bottom++;
        if (rows < bottom)
            y = y - ((bottom - rows) << 3);
    }
    *x_out = x;
    *y_out = y;
}
