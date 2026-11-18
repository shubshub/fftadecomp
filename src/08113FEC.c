#include "control_flags.h"

/* Registered by 08115560 with a 0x160-byte payload.
 * Complete Thumb function [0x08113FEC, 0x081141EA), including literal pools. */
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
    u8 unknown_00[8];
    s16 *x_out;
    s16 *y_out;
    u16 rows;
    u16 unknown_12;
    void *script;
    u16 palette[160];
    void *map_task;
    void *sound_task;
} Payload;

extern const u8 data_083A3958[];
extern const u8 data_083A3988[];
extern u8 data_0600CC00[], data_06007000[], data_06007800[];
extern void func_0801E6F0(u16 *, u16 *);
extern u16 func_0801BA20(s16, s16, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_0801BDB0(void);
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
extern const u8 *func_0801DC7C(s16);
extern void func_0801DCB8(const u16 *);
extern u8 *func_0801DC5C(void);
extern void func_08148318(const u16 *, u16 *, u16, u8);

static inline void get_map_bounds(MapBounds *bounds)
{
    func_0801CAE0(bounds->values);
}

u32 func_08113FEC(void *task, Descriptor *descriptor, Payload *payload)
{
    u16 x, y;
    u8 first_layer, second_layer;

    switch (descriptor->phase) {
    case 0:
        payload->x_out = descriptor->x_out;
        payload->y_out = descriptor->y_out;
        break;
    case 1:
        break;
    case 0x100:
        func_0801E6F0(&x, &y);
        x = 512;
        x -= 32;
        func_0801BA20((s16)x, (s16)y, 8);
        payload->sound_task = func_080DFD8C(data_083A3958, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (func_0801BDB0())
            break;
        func_0801E610(&first_layer, &second_layer);
        g_control_flags_03000940.display &= ~func_080035A8(first_layer);
        g_control_flags_03000940.display &= ~func_080035A8(second_layer);
        func_080DBED4(0, 0, 0, 0);
        {
            MapBounds bounds;
            get_map_bounds(&bounds);
            payload->map_task = func_080D89D0(4, 4, 0, 0, 0x260, 0x11D,
                data_0600CC00, data_06007000, 0x3FF,
                bounds.rect.left >> 3, bounds.rect.top >> 3,
                bounds.rect.width >> 3, bounds.rect.height >> 3, task);
        }
        func_080D8B18((u32)payload->map_task, (u32)&payload->rows);
        payload->script = func_080D3E9C(data_083A3988, task);
        g_control_flags_03000940.bldcnt_lo = 255;
        g_control_flags_03000940.bldy_lo = 8;
        func_0801DCB8((const u16 *)func_0801DC7C(-1));
        descriptor->phase++;
        break;
    case 0x102:
        payload->map_task = func_080D8AEC(payload->map_task);
        if (payload->map_task)
            break;
        func_08115A1C(120, 112, payload->rows, payload->x_out, payload->y_out);
        payload->script = func_080D3F08(payload->script);
        if (payload->script)
            break;
        func_08148318((const u16 *)func_0801DC5C(), payload->palette, 160, 4);
        func_0801DCB8(payload->palette);
        g_control_flags_03000940.bldcnt_lo = 0;
        func_08000B20(func_080D3AF8(), 0x3FF, (u32)data_06007800, 0x400);
        descriptor->phase++;
        break;
    case 0x103:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
