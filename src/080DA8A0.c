#include "ffta.h"

/*
 * 0x080DA8A0..0x080DA966: 198 bytes, 92 Thumb instructions.
 * Resolve the task's drawing buffer, draw a circle of the given radius with
 * value 1, then an ellipse with radii radius and radius >> 1 and value 2.
 * The ellipse is drawn by 080DA074 with the larger radius shifted by 4, scale
 * 0x100 on that axis and the squared-radius ratio (BIOS Div) on the other.
 * Only that branch can run here (radius >> 1 is below any nonzero radius),
 * but the ROM keeps the other two, height larger and equal radii (the circle
 * routine 080D9F60), as an inlined general routine would.
 * The two helpers are shared text: the same get_buffer and draw_ellipse
 * reproduce func_080DAC80 (draw_ellipse(x, y, width, height, buffer, 0)).
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

void func_080DA8A0(void *task, u16 x, u16 y, u16 radius)
{
    void *buffer = get_buffer(task);

    func_080D9F60(x, y, radius, buffer, 1);
    draw_ellipse(x, y, radius, radius >> 1, buffer, 2);
}
