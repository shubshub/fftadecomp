#include "ffta.h"

/* Complete [0x080DA074, 0x080DA1C4), 336 bytes. */
typedef struct __attribute__((packed)) {
    volatile u8 right : 8;
    volatile u8 left : 8;
} WindowLine;

extern s32 func_08141870(s32 numerator, s32 denominator);
extern u16 func_08141898(u32 value);

void func_080DA074(s32 x, s32 y, u32 size, u32 x_scale, u32 y_scale,
                   void *buffer, u8 mode)
{
    s32 width, offset;
    s32 vertical_error, horizontal_error;
    s32 change;
    s16 left, right, row;

    if (size == 0)
        return;
    width = func_08141870(size, func_08141898(x_scale));
    offset = 0;
    vertical_error = func_08141898(x_scale) * 2;
    vertical_error = -vertical_error;
    horizontal_error = func_08141898(x_scale) * 4;
    horizontal_error = -horizontal_error;
    vertical_error = vertical_error * size + x_scale + 2 * y_scale;
    horizontal_error = horizontal_error * size + 2 * x_scale + y_scale;
    while (width > 0) {
        left = x - width;
        if (left < 0)
            left = 0;
        right = x + width + 1;
        if (right > 240)
            right = 240;
        if (mode != 1) {
            row = y + offset;
            if ((u16)row < 160) {
                ((WindowLine *)buffer)[row].left = left;
                ((WindowLine *)buffer)[row].right = right;
            }
        }
        if (mode != 2) {
            row = y - offset;
            if ((u16)row < 160) {
                ((WindowLine *)buffer)[row].left = left;
                ((WindowLine *)buffer)[row].right = right;
            }
        }

        if (vertical_error < 0) {
            offset++;
            change = (y_scale << 2) * offset;
            vertical_error += change + 2 * y_scale;
            horizontal_error += change;
        } else if (horizontal_error >= 0) {
            width--;
            change = (x_scale * width) << 2;
            vertical_error -= change;
            horizontal_error -= change - 2 * x_scale;
        } else {
            width--;
            offset++;
            change = (y_scale * offset - x_scale * width) << 1;
            vertical_error += (change + y_scale) << 1;
            horizontal_error += (change + x_scale) << 1;
        }
    }
}
