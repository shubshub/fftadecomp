#include "ffta.h"

/*
 * 0x080DAC80..0x080DAD3A: 186 bytes, 87 Thumb instructions.
 * Resolve the task's drawing buffer and draw an ellipse with the given width
 * and height and value 0. The ellipse is drawn by 080DA074 with the larger
 * dimension shifted by 4, scale 0x100 on that axis and the squared-dimension
 * ratio (BIOS Div) on the other; equal dimensions call the circle routine
 * 080D9F60 and a zero dimension draws nothing.
 * The two helpers are shared text with func_080DA8A0, which uses the same
 * get_buffer and draw_ellipse.
 */

typedef struct {
    u8 unknown_0[4];
    void *object;
} DrawingState;

extern DrawingState *func_08005BFC(void *task);
extern void *func_0800C614(void *object);
extern void func_080D9F60(s16 x, s16 y, u16 radius, void *buffer, u8 value);
extern void func_080DA074(s32 x, s32 y, u32 size, u32 x_scale, u32 y_scale,
                          void *buffer, u8 value);
extern s32 func_08141870(s32 numerator, s32 denominator);

static inline void *get_buffer(void *task)
{
    return func_0800C614(func_08005BFC(task)->object);
}

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

void func_080DAC80(void *task, s16 x, s16 y, u16 width, u16 height)
{
    void *buffer = get_buffer(task);

    draw_ellipse(x, y, width, height, buffer, 0);
}
