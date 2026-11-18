#include "control_flags.h"

/* Registered by 08113CE0 with a 0x1C-byte payload.
 * Complete Thumb function [0x08112AEC, 0x08112CCC), including literal pools. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    s16 *x_out;
    s16 *y_out;
} Descriptor;

typedef union {
    s16 values[6];
    struct {
        s16 left, top, right, bottom;
        u16 width, height;
    } rect;
} MapBounds;

typedef struct {
    u8 unknown_00[6];
    u16 rows;
    s16 *x_out;
    s16 *y_out;
    void *script;
    void *map_task;
    void *sound_task;
} Payload;

extern const u8 data_083A3798[];
extern const u8 data_088F5F08[];
extern const u8 data_0894DBF4[];
extern u8 data_0600CC00[], data_06007000[], data_06007800[];
extern u16 data_03003860[];
extern void func_0801E6F0(u16 *, u16 *);
extern u16 func_0801BA20(s16, s16, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_0801BDB0(void);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void func_0801E610(u8 *, u8 *);
extern u16 func_080035A8(u8);
extern void func_080DBED4(u8, u8, void *, void *);
extern void func_0801CAE0(s16 *);
extern void *func_080D89D0(u8, u8, u8, u8, u16, u16, void *, void *, u16,
                           u8, u8, u8, u8, void *);
extern void func_080D8B18(u32, u32);
extern void *func_080D3F08(void *);
extern void *func_080D8AEC(void *);
extern void func_08115A1C(u32, u16, u16, s16 *, s16 *);
extern void *func_080D3AF8(void);
extern void func_08000B20(void *, u16, u32, u16);
extern void func_0801DB78(void);

static inline void get_map_bounds(MapBounds *bounds)
{
    func_0801CAE0(bounds->values);
}

u32 func_08112AEC(void *task, Descriptor *descriptor, Payload *payload)
{
    u16 x, y;
    u8 first_layer, second_layer;
    s32 pan_y;

    switch (descriptor->phase) {
    case 0:
        payload->x_out = descriptor->x_out;
        payload->y_out = descriptor->y_out;
        break;
    case 1:
        break;
    case 0x100:
        func_0801E6F0(&x, &y);
        pan_y = -192;
        y = pan_y;
        func_0801BA20((s16)x, pan_y, 8);
        payload->sound_task = func_080DFD8C(data_083A3798, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (func_0801BDB0())
            break;
        func_080D7220(data_088F5F08, 0, 2, 0, 0, 0);
        payload->script = func_080D3E9C(data_0894DBF4, task);
        func_0801E610(&first_layer, &second_layer);
        g_control_flags_03000940.display &= ~func_080035A8(first_layer);
        g_control_flags_03000940.display &= ~func_080035A8(second_layer);
        func_080DBED4(0, 0, 0, 0);
        {
            MapBounds bounds;
            get_map_bounds(&bounds);
            payload->map_task = func_080D89D0(4, 4, 0, 0, 0x260, 0x136,
                data_0600CC00, data_06007000, 0x3FF,
                bounds.rect.left >> 3, bounds.rect.top >> 3,
                bounds.rect.width >> 3, bounds.rect.height >> 3, task);
        }
        func_080D8B18((u32)payload->map_task, (u32)&payload->rows);
        descriptor->phase++;
        break;
    case 0x102:
        payload->script = func_080D3F08(payload->script);
        if (payload->script)
            break;
        payload->map_task = func_080D8AEC(payload->map_task);
        if (payload->map_task)
            break;
        func_08115A1C(120, 112, payload->rows, payload->x_out, payload->y_out);
        func_08000B20(func_080D3AF8(), 0x3FF, (u32)data_06007800, 0x400);
        func_0801DB78();
        descriptor->phase++;
        break;
    case 0x103:
        data_03003860[0] = 0x65C9;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        descriptor->phase = 2;
        break;
    }
    return 0;
}
