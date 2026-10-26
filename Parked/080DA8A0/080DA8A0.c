#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    void *object;
} DrawingState;

extern DrawingState *func_08005BFC(void *object);
extern void *func_0800C614(void *object);
extern void func_080D9F60(s16 x, s16 y, u16 radius, void *buffer, u32 value);
extern void func_080DA074(s16 x, s16 y, u32 radius, u32 x_scale,
                         u32 y_scale, void *buffer, u32 value);
extern u32 func_08141870(u32 numerator, u32 denominator);

static inline void draw_ellipse(s16 x, s16 y, u16 width, u16 height,
                                void *buffer, u32 value)
{
    u32 extent;
    u32 x_scale;
    u32 y_scale;

    if (width && height) {
        if (width > height) {
            extent = width << 4;
            x_scale = 0x100;
            y_scale = func_08141870((width * width) << 8, height * height);
            func_080DA074(x, y, extent, x_scale, y_scale, buffer, value);
        } else if (width < height) {
            extent = height << 4;
            x_scale = func_08141870((height * height) << 8, width * width);
            y_scale = 0x100;
            func_080DA074(x, y, extent, x_scale, y_scale, buffer, value);
        } else {
            func_080D9F60(x, y, width, buffer, value);
        }
    }
}

void func_080DA8A0(void *object, u16 x, u16 y, u16 radius)
{
    void *buffer = func_0800C614(func_08005BFC(object)->object);

    func_080D9F60((s16)x, (s16)y, radius, buffer, 1);
    draw_ellipse((s16)x, (s16)y, radius, radius >> 1, buffer, 2);
}
