#include "ffta.h"

/* Complete [0x080DA1C4, 0x080DA2D4), 272 bytes. */
typedef struct __attribute__((packed)) {
    volatile u8 right : 8;
    volatile u8 left : 8;
} WindowLine;

extern void func_080D9F60(s16 x, s16 y, u16 radius, void *buffer, u8 value);
extern void func_080DA074(s32 x, s32 y, u32 size, u32 x_scale, u32 y_scale,
                          void *buffer, u8 value);
extern s32 func_08141870(s32 numerator, s32 denominator);

static inline void draw_ellipse(s16 x, s16 y, u16 width, u16 height,
                                void *buffer, u8 value)
{
    u32 size;
    u32 x_scale;
    u32 y_scale;

    if (width && height) {
        if (width > height) {
            size = width << 4;
            x_scale = 0x100;
            y_scale = func_08141870((width * width) << 8, height * height);
            func_080DA074(x, y, size, x_scale, y_scale, buffer, value);
        } else if (width < height) {
            size = height << 4;
            x_scale = func_08141870((height * height) << 8, width * width);
            y_scale = 0x100;
            func_080DA074(x, y, size, x_scale, y_scale, buffer, value);
        } else {
            func_080D9F60(x, y, width, buffer, value);
        }
    }
}

void func_080DA1C4(s16 x, s16 y, u16 diameter, void *buffer)
{
    u16 radius = diameter >> 1;
    u8 row;

    draw_ellipse(x, y, radius, radius >> 1, buffer, 2);
    for (row = 0; row < y; row++) {
        ((WindowLine *)buffer)[row].left = x - radius;
        ((WindowLine *)buffer)[row].right = x + radius;
    }
    if (!(diameter & 1)) {
        for (row = 0; row < y + radius && row < 160; row++) {
            if (((WindowLine *)buffer)[row].right > ((WindowLine *)buffer)[row].left)
                ((WindowLine *)buffer)[row].right--;
        }
    }
}
