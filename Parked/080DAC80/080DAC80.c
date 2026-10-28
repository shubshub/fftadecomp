#include "ffta.h"

/* 0x080DAC80..0x080DAD3A: 186 bytes, 87 instructions. */
typedef struct {
    u8 unknown_00[4];
    void *object;
} TaskRecord;

extern TaskRecord *func_08005BFC(void *task);
extern void *func_0800C614(void *object);
extern void func_080DA074(s32 x, s32 y, s32 size, s32 scale_x,
                         s32 scale_y, void *output, u32 flags);
extern void func_080D9F60(s32 x, s32 y, s32 size, void *output, u32 flags);

static inline void draw_shape(s32 x, s32 y, u32 width, u32 height, void *output)
{
    s32 size = width;
    s32 scale_x = height;

    if (width && height) {
        if (width > height) {
            size = width << 4;
            scale_x = 0x100;
            func_080DA074(x, y, size, scale_x,
                         (s32)((width * width) << 8) / (s32)(height * height), output, 0);
        } else if (width < height) {
            size = height << 4;
            scale_x = (s32)((height * height) << 8) / (s32)(width * width);
            func_080DA074(x, y, size, scale_x, 0x100, output, 0);
        } else {
            func_080D9F60(x, y, size, output, 0);
        }
    }
}

void func_080DAC80(void *task, u16 x, u16 y, u16 width, u16 height)
{
    void *output = func_0800C614(func_08005BFC(task)->object);
    draw_shape((s16)x, (s16)y, width, height, output);
}
