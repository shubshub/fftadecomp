#include "ffta.h"

/* Target: 0800ED58..0800F068, 784 bytes. */
struct ScanlineWindow0800ED58 {
    u16 left;
    u16 right;
};
extern u8 data_02009160;
extern s32 func_08141870(s32 numerator, s32 denominator);
extern void func_0800E878(s16 x, s16 y, u16 radius,
                        struct ScanlineWindow0800ED58 *lines, u8 clipped, u8 direction);

void func_0800ED58(u16 x, u16 y, u16 radius_x, u16 radius_y,
                   struct ScanlineWindow0800ED58 *lines, u8 clipped, u8 direction)
{
    if (radius_x == 0 || radius_y == 0)
        return;
    if (clipped == 0) {
        if (direction == 0)
            y = radius_y;
        else
            y = 0;
    }
    if (radius_x == radius_y) {
        func_0800E878((s16)x, (s16)y, radius_y, lines, clipped, direction);
        return;
    }
    if (radius_x > radius_y) {
        s16 center_x = x;
        s16 center_y = y;
        s16 minor = 0;
        s32 cached = 0;
        s16 previous = 0xffff;
        s16 major = radius_x;
        u16 error = radius_x;
        while ((s16)major >= (s16)minor) {
            s32 scaled;
            u16 left, right;
            s32 row;
            if ((s16)major != (s16)previous) {
                cached = func_08141870((s16)major * radius_y, radius_x);
                previous = major;
            }
            scaled = func_08141870((s16)minor * radius_y, radius_x);
            left = center_x - (s16)major;
            right = center_x + (s16)major + data_02009160;
            if (direction == 1)
                row = (s16)(center_y + scaled);
            else if (direction == 0)
                row = (s16)(center_y - scaled);
            else
                goto next_scanline_1;
            if (row >= 0 && (!clipped || row <= 159)) {
                lines[row].left = left;
                lines[row].right = right;
            }
next_scanline_1: ;
            left = center_x - (s16)minor;
            right = center_x + (s16)minor + data_02009160;
            if (direction == 1)
                row = (s16)(center_y + cached);
            else if (direction == 0)
                row = (s16)(center_y - cached);
            else
                goto next_scanline_2;
            if (row >= 0 && (!clipped || row <= 159)) {
                lines[row].left = left;
                lines[row].right = right;
            }
next_scanline_2: ;
            error = (s16)error + 1 - (s16)minor++ * 2;
            if ((s16)error < 0) {
                error = (s16)error + (s16)major * 2 - 2;
                major--;
            }
        }
    } else {
        s16 center_x = x;
        s16 center_y = y;
        s16 minor = 0;
        s32 cached = 0;
        s16 previous = 0xffff;
        s16 major = radius_y;
        u16 error = radius_y;
        while ((s16)major >= (s16)minor) {
            s32 scaled;
            u16 left, right;
            s32 row;
            if ((s16)major != (s16)previous) {
                cached = func_08141870((s16)major * radius_x, radius_y);
                previous = major;
            }
            scaled = func_08141870((s16)minor * radius_x, radius_y);
            left = center_x - cached;
            right = center_x + cached + data_02009160;
            if (direction == 1)
                row = (s16)(center_y + (s16)minor);
            else if (direction == 0)
                row = (s16)(center_y - (s16)minor);
            else
                goto next_scanline_3;
            if (row >= 0 && (!clipped || row <= 159)) {
                lines[row].left = left;
                lines[row].right = right;
            }
next_scanline_3: ;
            left = center_x - scaled;
            right = center_x + scaled + data_02009160;
            if (direction == 1)
                row = (s16)(center_y + (s16)major);
            else if (direction == 0)
                row = (s16)(center_y - (s16)major);
            else
                goto next_scanline_4;
            if (row >= 0 && (!clipped || row <= 159)) {
                lines[row].left = left;
                lines[row].right = right;
            }
next_scanline_4: ;
            error = (s16)error + 1 - (s16)minor++ * 2;
            if ((s16)error < 0) {
                error = (s16)error + (s16)major * 2 - 2;
                major--;
            }
        }
    }
}
