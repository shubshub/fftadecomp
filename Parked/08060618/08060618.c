#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08017B68;

typedef struct {
    u8 unknown_00[0x11];
    s8 value_11;
} Cursor08060618;

typedef struct {
    u8 unknown_00[9];
    u8 value_09;
} Flags08060618;

typedef struct {
    u8 value_00;
    u8 unknown_01[0x0B];
    u32 value_0C;
    u8 unknown_10[0x2C];
    ClampState08017B68 list;
    u8 unknown_58[4];
    Cursor08060618 cursor;
    u8 unknown_70[0x14];
    Flags08060618 flags;
} Menu;

typedef struct {
    u16 unknown_00;
    u16 value_02;
} Input08060618;

typedef struct {
    u8 unknown_00[0x14];
    u16 value_14;
    u8 value_16;
    u8 value_17;
    u8 unknown_18[6];
    u16 value_1E;
} State08060618;

extern Input08060618 data_03000000;
extern State08060618 *data_0200F44C;

extern u16 func_08017B68(ClampState08017B68 *state, u32 index);
extern u16 func_08060580(const u8 *mode, s16 selection);
extern s16 func_08060468(const u8 *mode, s16 selection, u8 *confirmed);
extern s16 func_08060544(void *unused, s16 index);
extern void func_08141540(u16 song_id);
extern void func_08141570(s32 player_id, u16 song_id);
extern u32 func_0805FA4C(Menu *menu);
extern u32 func_0805F824(Menu *menu);
extern void func_0805F69C(Menu *menu);

/* Complete target: [0x08060618, 0x08060828), 528 bytes.
 * 70b581b0051c2e1c8436002168460170104844880420204000281fd0281c3c30291c6d31
 * 097809060916b7f791fa011c09040914281cfff797ff011c06480268d1830804002809d0
 * 481ed083082090750120d9e0000000034cf4000202202040002817d001206921e0f076ff
 * 717a08200840002806d0024a1168022005e000004cf40002024a116801208875116878e0
 * 4cf4000201202040002845d0281c3c30291c6d31097809060916b7f751fa011c09040914
 * 281c6a46fff7cafe0004040c001402214942884204d101206b21e0f043ff98e0717a0422
 * 101c0840002805d001480068827505e04cf40002054801680320887568460078002805d0
 * 9c20e0f013ff0ce04cf400022004002803db6420e0f00aff03e001206b21e0f01dff0148
 * 01682de04cf40002717a2020084000282ed0802080002040002829d0281c3c30291c6d31
 * 097809060916b7f701fa011c09040914281cfff7e9fe0004040c0114022040428142b0d0
 * 0229aed0012902dc9c20e0f0d9fe054a11680620887511688c822878c87501203ee00000
 * 4cf400024020084000280fd0802040000440002c0ad0e868002807d00248016807208875
 * 012029e04cf400020120084000280cd0281cfff723f8000600281cd0e868002819d0281c
 * fef756ff15e002200840002811d0281cfff726f90006040e002c05d0e868002802d0281c
 * fef744ff0020022c02d1012000e0002001b070bc02bc0847
 */
u32 func_08060618(Menu *menu)
{
    Flags08060618 *flags = &menu->flags;
    u8 confirmed = 0;
    u16 input = data_03000000.value_02;

    if (input & 4) {
        data_0200F44C->value_1E = func_08060580(&menu->value_00,
            (s16)func_08017B68(&menu->list, menu->cursor.value_11));

        if (data_0200F44C->value_1E != 0) {
            data_0200F44C->value_1E--;
            data_0200F44C->value_16 = 8;
            return 1;
        }
    }

    if (input & 2) {
        func_08141570(1, 0x69);
        if (flags->value_09 & 8)
            data_0200F44C->value_16 = 2;
        else
            data_0200F44C->value_16 = 1;
        data_0200F44C->value_17 = menu->value_00;
        return 1;
    } else if (input & 1) {
        u16 selection = func_08060468(&menu->value_00,
            (s16)func_08017B68(&menu->list, menu->cursor.value_11), &confirmed);

        if ((s16)selection == -2) {
            func_08141570(1, 0x6B);
            return 0;
        }
        if (flags->value_09 & 4)
            data_0200F44C->value_16 = 4;
        else
            data_0200F44C->value_16 = 3;
        if (confirmed)
            func_08141540(0x9C);
        else if ((s16)selection >= 0)
            func_08141540(0x64);
        else
            func_08141570(1, 0x6B);
        data_0200F44C->value_14 = selection;
        data_0200F44C->value_17 = menu->value_00;
        return 1;
    } else if ((flags->value_09 & 0x20) && (input & 0x200)) {
        u16 selection = func_08060544(menu,
            (s16)func_08017B68(&menu->list, menu->cursor.value_11));

        if ((s16)selection == -2 || (s16)selection == 2) {
            func_08141570(1, 0x6B);
            return 0;
        }
        if ((s16)selection <= 1)
            func_08141540(0x9C);
        data_0200F44C->value_16 = 6;
        data_0200F44C->value_14 = selection;
        data_0200F44C->value_17 = menu->value_00;
        return 1;
    } else if ((flags->value_09 & 0x40) && (input & 0x100) && menu->value_0C) {
        data_0200F44C->value_16 = 7;
        return 1;
    } else if (flags->value_09 & 1) {
        if ((u8)func_0805F824(menu) && menu->value_0C)
            func_0805F69C(menu);
    } else if (flags->value_09 & 2) {
        u8 result = func_0805FA4C(menu);

        if (result != 0 && menu->value_0C)
            func_0805F69C(menu);
        return result == 2;
    }
    return 0;
}
