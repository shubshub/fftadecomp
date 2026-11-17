// Complete target [0x0804D9D0, 0x0804DBF8), 552 bytes including literal pools.
#include "ffta.h"
#include "control_flags.h"

typedef struct {
    volatile u16 *control;
    volatile u16 *x_offset;
    volatile u16 *y_offset;
    u8 width;
    u8 height;
    u8 unknown_0E[2];
    u8 *tiles;
    u16 *map;
} Layer0804D9D0;

typedef struct {
    u8 unknown_0000[0x2FC2];
    u8 mode : 2;
    u8 unknown_02 : 6;
} Selection0804D9D0;

typedef void (*BufferCopier0804D9D0)(void *destination, const void *source,
                                    u32 size);

extern Layer0804D9D0 data_03000E60;
extern Layer0804D9D0 data_03000E80;
extern Layer0804D9D0 data_030008B0;
extern Layer0804D9D0 data_03000990;
extern Selection0804D9D0 g_state_02000000;
extern BufferCopier0804D9D0 data_0836D4BC[];
extern u16 data_03003860[];
extern u8 data_06005000[];
extern u8 data_06006000[];
extern u8 data_06007000[];
extern u8 data_06007800[];
extern u8 data_06008000[];
extern const u16 data_0841A780[];
extern const u16 data_0841B280[];
extern const u16 data_0841BD60[];

extern void func_0801E458(u8 layer, u8 format, u8 mode, s16 x, s16 y,
                          void *source, void *destination);
extern void *func_0804CA8C(void);
extern void func_08000B20(void *request, u32 value, void *destination, u32 count);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern const u16 *func_080CBA3C(u8 index);
extern const u8 *func_080CBA84(u32 index);
extern void func_08142250(void *destination, const void *source, u32 size,
                          BufferCopier0804D9D0 callback);
extern void func_08148318(const u16 *, u16 *, u16, u8);

void func_0804D9D0(void)
{
    u16 fill;
    u16 *source;
    u16 zero0;
    u16 zero1;
    u16 zero2;
    const u16 *palette;

    func_0801E458(0, 2, 1, 0, 0, (void *)0x06000000, data_06005000);
    func_0801E458(1, 2, 2, 0, 0, data_06008000, data_06006000);
    func_0801E458(2, 0, 0, 0, 0, data_06008000, data_06007000);
    func_0801E458(3, 0, 0, 0, 0, data_06008000, data_06007800);

    data_03000E60.control = (volatile u16 *)&g_control_flags_03000940 + 1;
    data_03000E60.x_offset = (volatile u16 *)&g_control_flags_03000940 + 5;
    data_03000E60.y_offset = (volatile u16 *)&g_control_flags_03000940 + 6;
    data_03000E80.control = (volatile u16 *)&g_control_flags_03000940 + 2;
    data_03000E80.x_offset = (volatile u16 *)&g_control_flags_03000940 + 7;
    data_03000E80.y_offset = (volatile u16 *)&g_control_flags_03000940 + 8;
    data_030008B0.control = (volatile u16 *)&g_control_flags_03000940 + 3;
    data_030008B0.x_offset = (volatile u16 *)&g_control_flags_03000940 + 9;
    data_030008B0.y_offset = (volatile u16 *)&g_control_flags_03000940 + 10;
    data_03000990.control = (volatile u16 *)&g_control_flags_03000940 + 4;
    data_03000990.x_offset = (volatile u16 *)&g_control_flags_03000940 + 11;
    data_03000990.y_offset = (volatile u16 *)&g_control_flags_03000940 + 12;

    g_control_flags_03000940.bldcnt_lo = g_control_flags_03000940.bldcnt_hi = 0;
    g_control_flags_03000940.bldalpha_lo = g_control_flags_03000940.bldalpha_hi = 0;
    g_control_flags_03000940.display = 0x840;

    source = &fill;
    *source = 0x1111;
    func_0814186C(source, data_03000990.tiles + 0x7FE0, 0x01000010);
    func_08000B20(func_0804CA8C(), 0xC3FF, data_03000990.map,
                  data_03000990.width * data_03000990.height);
    zero0 = 0;
    func_0814186C(&zero0, data_03000E60.map,
                  (data_03000E60.width * data_03000E60.height) | 0x01000000);
    zero1 = 0;
    func_0814186C(&zero1, data_03000E80.map,
                  (data_03000E80.width * data_03000E80.height) | 0x01000000);
    zero2 = 0;
    func_0814186C(&zero2, data_030008B0.map,
                  (data_030008B0.width * data_030008B0.height) | 0x01000000);

    {
        BufferCopier0804D9D0 *copy = data_0836D4BC;

        func_08142250(data_03003860 + 0x100, func_080CBA3C(0), 0x200, copy[0]);
        func_08142250(data_03003860, func_080CBA84(0), 0x200, copy[0]);
    }

    switch (g_state_02000000.mode) {
    case 2:
        palette = data_0841B280;
        break;
    case 1:
        palette = data_0841BD60;
        break;
    case 0:
    default:
        palette = data_0841A780;
        break;
    }
    {
        BufferCopier0804D9D0 *copy = data_0836D4BC;

        func_08142250(data_03003860, palette, 0xA0, copy[0]);
    }
    data_03003860[0] = 0;
    func_08148318(data_03003860 + 0xD0, data_03003860 + 0x60, 0x30, 6);
}
