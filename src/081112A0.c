#include "control_flags.h"

/* Complete Thumb function [0x081112A0, 0x0811166A), 970 bytes including
 * literal pools. */
typedef struct {
    s16 *x_out;
    s16 *y_out;
} Target;

typedef struct {
    u16 phase;
    u16 unknown_02;
    u8 *done;
    void **object_out;
    Target *target;
} Descriptor;

typedef union {
    s16 values[6];
    struct {
        s16 left, top, right, bottom;
        u16 width, height;
    } rect;
} MapBounds;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u16 timer;
    u8 unknown_02[6];
    s16 *x_out;
    s16 *y_out;
    u16 rows;
    u16 unknown_12;
    u8 *done;
    void **object_out;
    void *window;
    void *script;
    void *map_task;
    void *sound_task;
} Payload;

extern const u8 data_083A33AC[];
extern const u8 data_083A33B4[];
extern const u8 data_083A33E4[];
extern const u8 data_083A33EE[];
extern const u8 data_088F11D0[];
extern const u8 data_088F5D28[];
extern const u8 data_0894DBC0[];
extern const u8 data_08504C6C[];
extern u8 data_0600CC00[], data_06007000[], data_06007800[];
extern void func_0801E6F0(u16 *, u16 *);
extern u16 func_0801BA20(s16, s16, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_0801BDB0(void);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void func_0800BC90(u8, u8, u8);
extern void func_0800BD24(u8, u8);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void *func_080D3E9C(const void *, void *);
extern u16 func_080035A8(u8);
extern void func_0801E610(u8 *, u8 *);
extern void func_080DBED4(u8, u8, void *, void *);
extern void func_0801CAE0(s16 *);
extern void *func_080D89D0(u8, u8, u8, u8, u16, u16, void *, void *, u16,
                           u8, u8, u8, u8, void *);
extern void func_080D8B18(u32, u32);
extern void func_080D3EFC(void *);
extern void func_0800BD7C(void *);
extern void *func_080D8AEC(void *);
extern void func_08115A1C(u32, u16, u16, s16 *, s16 *);
extern void func_0800BD90(void *);
extern void func_080D72C8(const void *, u8, u8, s16, s16, u16, u8);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void *func_080D3AF8(void);
extern void func_08000B20(void *, u16, u32, u16);
extern u8 *func_0801DC5C(void);
extern void func_0814186C(const void *, void *, u32);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern void *func_080D3F08(void *);
extern void func_080D4D14(void *, u8);

/* Bounds and the red ramp share sp+0x30 (0x0811140C, 0x08111564): the
 * bounds are the helper's own local, released when it returns. */
static inline void *create_map_task(void *task)
{
    MapBounds bounds;

    func_0801CAE0(bounds.values);
    return func_080D89D0(4, 4, 0, 0, 0x260, 0x11D,
        data_0600CC00, data_06007000, 0x3FF,
        bounds.rect.left >> 3, bounds.rect.top >> 3,
        bounds.rect.width >> 3, bounds.rect.height >> 3, task);
}

u32 func_081112A0(void *task, Descriptor *descriptor, Payload *payload)
{
    u16 x, y;
    u8 first_layer, second_layer;
    s32 pan_y;

    switch (descriptor->phase) {
    case 0:
        payload->done = descriptor->done;
        payload->object_out = descriptor->object_out;
        payload->x_out = descriptor->target->x_out;
        payload->y_out = descriptor->target->y_out;
        break;
    case 0x100:
        func_0801E6F0(&x, &y);
        pan_y = -192;
        y = pan_y;
        func_0801BA20((s16)x, pan_y, 8);
        payload->sound_task = func_080DFD8C(data_083A33AC, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (func_0801BDB0())
            break;
        func_080D49FC(1, 3, 0, 0, 0);
        func_0800BC90(1, 0, 3);
        func_0800BD24(1, 0);
        payload->window = func_080D4B64(1, data_088F11D0, 0x3A2, 7);
        payload->script = func_080D3E9C(data_0894DBC0, task);
        g_control_flags_03000940.display |= func_080035A8(3);
        descriptor->phase++;
        break;
    case 0x102:
        func_0801E610(&first_layer, &second_layer);
        g_control_flags_03000940.display &= ~func_080035A8(first_layer);
        g_control_flags_03000940.display &= ~func_080035A8(second_layer);
        func_080DBED4(0, 0, 0, 0);
        payload->map_task = create_map_task(task);
        func_080D8B18((u32)payload->map_task, (u32)&payload->rows);
        payload->timer = 30;
        descriptor->phase++;
        break;
    case 0x103:
        if (--payload->timer)
            break;
        func_080D3EFC(payload->script);
        payload->script = 0;
        func_0800BD7C(payload->window);
        descriptor->phase++;
        break;
    case 0x104:
        payload->map_task = func_080D8AEC(payload->map_task);
        if (payload->map_task)
            break;
        func_08115A1C(120, 106, payload->rows, payload->x_out, payload->y_out);
        func_0800BD90(payload->window);
        payload->script = func_080D3E9C(data_083A33E4, task);
        func_080D72C8(data_088F5D28, 0, 2, 0, 0, 0, 3);
        *payload->object_out = func_080D5CC0(data_08504C6C, 0, 120, 64, 0x38F,
                                             6, 1, 0);
        func_08000B20(func_080D3AF8(), 0x3FF, (u32)data_06007800, 0x400);
        payload->sound_task = func_080DFD8C(data_083A33B4, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x105: {
        u16 *palette = (u16 *)func_0801DC5C();
        InterpolationState red, green, blue;
        u16 fill, color;
        u16 *fill_source;
        u16 *color_source;
        u16 i;

        /* CpuFill16(0, palette, 0x80) and CpuFill16(RGB(4, 14, 19),
         * palette + 0x88, 0x30): the SDK's vu16 temporaries, spelled
         * through a pointer until fftadecomp-kit#164 (0x081115C8 loads
         * the colour apart from its store). */
        fill_source = &fill;
        *fill_source = 0;
        func_0814186C(fill_source, palette, 0x01000040);
        func_080E0608(&red, 0, 4, 72);
        func_080E0608(&green, 0, 14, 72);
        func_080E0608(&blue, 0, 19, 72);
        for (i = 0; i < 72; i++) {
            func_080E064C(&red);
            func_080E064C(&green);
            func_080E064C(&blue);
            palette[0x40 + i] = red.current | (green.current << 5)
                              | (blue.current << 10);
        }
        color_source = &color;
        *color_source = 0x4DC4;
        func_0814186C(color_source, palette + 0x88, 0x01000018);
        descriptor->phase++;
        break;
    }
    case 0x106:
        payload->script = func_080D3F08(payload->script);
        if (payload->script)
            break;
        payload->script = func_080D3E9C(data_083A33EE, task);
        descriptor->phase++;
        break;
    case 0x107:
        payload->script = func_080D3F08(payload->script);
        if (payload->script)
            break;
        payload->timer = 7;
        descriptor->phase++;
        break;
    case 0x108:
        if (payload->timer) {
            if (--payload->timer)
                break;
            func_080D4D14(payload->window, 1);
            payload->window = 0;
            *payload->done = 1;
        }
        if (payload->timer == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
