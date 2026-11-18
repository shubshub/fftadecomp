#include "ffta.h"

typedef struct {
    u16 kind;
    u16 x;
    u16 y;
    u16 offset_x;
    u16 offset_y;
    u16 unknown_0A;
    s32 x_fixed;
    s32 y_fixed;
    s16 base_screen_x;
    s16 base_screen_y;
    u16 scale_x;
    u16 scale_y;
    u32 unknown_1C;
    s32 start_x_fixed;
    s32 start_y_fixed;
    s16 line_screen_x;
    s16 line_screen_y;
    u16 start_scale_x;
    u16 start_scale_y;
    u32 unknown_30;
    u16 radius;
} AffineWave;

typedef struct {
    u16 *destinations[2];
} AffineTargets;

extern const AffineTargets data_08149820;
extern void func_0800D3BC(void *state, u16 *destination);
typedef struct ScanlineTask ScanlineTask;
struct Object0800C614;

extern ScanlineTask *func_0800C3CC(void (*callback)(void *, u16 *), u16 payload_bytes,
                               u16 element_size, u16 *destination);
extern void *func_0800C614(const struct Object0800C614 *object);
extern void func_0800C9E4(AffineWave *window, u32 mode);

void *func_0800CFC8(u8 target, u16 x, u16 y, u16 radius,
                    u16 offset_x, u16 offset_y)
{
    void *object;
    AffineTargets targets = data_08149820;
    AffineWave *window;
    s32 left;
    s32 top;
    s32 span_x;
    s32 span_y;

    object = func_0800C3CC(func_0800D3BC, 0x2B8, 0x10,
                           targets.destinations[target - 2]);
    window = func_0800C614(object);
    window->kind = 1;
    window->x = x;
    window->y = y;
    window->offset_x = offset_x;
    window->offset_y = offset_y;
    left = (s16)x;
    window->x_fixed = left * 256;
    top = (s16)y;
    window->y_fixed = top * 256;
    span_x = (s16)offset_x;
    window->base_screen_x = left + span_x;
    span_y = (s16)offset_y;
    window->base_screen_y = top + span_y;
    window->scale_x = 0x100;
    window->scale_y = 0x100;
    window->start_x_fixed = left * 256;
    window->start_y_fixed = top * 256;
    window->line_screen_x = left + span_x;
    window->line_screen_y = top + span_y;
    window->start_scale_x = 0x100;
    window->start_scale_y = 0x100;
    window->radius = radius;
    func_0800C9E4(window, 1);
    return object;
}
