#include "ffta.h"

// Target: complete [0x0800D090, 0x0800D168), 216 bytes.

typedef struct {
    u16 kind;
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 unknown_0A;
    s32 x_fixed;
    s32 y_fixed;
    s16 right;
    s16 bottom;
    u16 scale_x;
    u16 scale_y;
    u32 unknown_1C;
    s32 start_x_fixed;
    s32 start_y_fixed;
    s16 start_right;
    s16 start_bottom;
    u16 start_scale_x;
    u16 start_scale_y;
    u32 unknown_30;
    u16 unknown_34;
    u16 unknown_36;
} Window0800D090;

typedef struct {
    u16 *destinations[2];
} Targets0800D090;

extern const Targets0800D090 data_08149820;
extern void func_0800D3BC(void *state, u16 *destination);
extern void *func_0800C3CC(void (*callback)(void *, u16 *), u16 payload_bytes,
                           u16 element_size, u16 *destination);
extern Window0800D090 *func_0800C614(void *object);
extern void func_0800CAF0(Window0800D090 *window, u32 mode);

void *func_0800D090(u8 target, u16 x, u16 y, u16 unknown_34, u16 unknown_36,
                    u16 width, u16 height)
{
    void *object;
    Targets0800D090 targets = data_08149820;
    Window0800D090 *window;
    s32 left;
    s32 top;
    s32 span_x;
    s32 span_y;

    object = func_0800C3CC(func_0800D3BC, 0x2B8, 0x10,
                           targets.destinations[target - 2]);
    window = func_0800C614(object);
    window->kind = 2;
    window->x = x;
    window->y = y;
    window->width = width;
    window->height = height;
    left = (s16)x;
    window->x_fixed = left << 8;
    top = (s16)y;
    window->y_fixed = top << 8;
    span_x = (s16)width;
    window->right = left + span_x;
    span_y = (s16)height;
    window->bottom = top + span_y;
    window->scale_x = 0x100;
    window->scale_y = 0x100;
    window->start_x_fixed = left << 8;
    window->start_y_fixed = top << 8;
    window->start_right = left + span_x;
    window->start_bottom = top + span_y;
    window->start_scale_x = 0x100;
    window->start_scale_y = 0x100;
    window->unknown_34 = unknown_34;
    window->unknown_36 = unknown_36;
    func_0800CAF0(window, 1);
    return object;
}
