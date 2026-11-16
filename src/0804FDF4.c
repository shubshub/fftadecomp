#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 *row;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16[8];
    u8 stride;
} Menu0804FDF4;

typedef struct {
    u8 unknown_00[0x48];
    Menu0804FDF4 menu;
    u8 unknown_68[0x28];
    s8 *enabled;
} State0804FDF4;

extern const u16 g_table_08529EE4[];
extern u32 func_080CE4DC(u16 index, u8 selector);
extern u32 func_080CB9CC(u16 category);
extern u16 func_080161A0(u8 x, u8 y, u8 width);

/* Complete target [0x0804FDF4, 0x0804FF48): 340 bytes, 135 instructions.
 * f0b557464e464546e0b4071c0904090c8a461204120c9146
 * 1b041b0c1d1c4820c01980461b49681e400040180488201c
 * 02217ef059fb0006f02109054018060e201c01217ef050fb
 * 012800d10626381c90300068281801380078000600160028
 * 00d11326301c7bf0b7fd0006040e4a46002a05d0132e03d1
 * 201cf9300006040ee025b01f0c282ed88000034940180068
 * 87460000e49e520890fe0408d4fe0408dafe0408dafe0408
 * dafe0408dafe0408dafe0408dafe0408dafe0408dafe0408
 * e2fe0408c4fe0408cefe0408c8fe0408281d0ae0281c0c30
 * 07e0281c083004e0281c103001e0281c14300004050c5346
 * 1806000e4a461106090e43469a7fc6f755f90004c00b4146
 * cb681b18291c481c0004050c2a1c240321431980501c0004
 * 050c291c22435a804246507d40001b18481c0004000c2143
 * 1980204358800020132e00d1012038bc9846a146aa46f0bc
 * 02bc0847
 */
u32 func_0804FDF4(State0804FDF4 *state, u16 x, u16 y, u16 selection)
{
    Menu0804FDF4 *menu = &state->menu;
    u16 id = g_table_08529EE4[selection - 1];
    u8 category = func_080CE4DC(id, 2);
    u8 palette;
    u16 tile;
    u16 *tiles;

    category += 15;
    if (func_080CE4DC(id, 1) == 1)
        category = 6;
    if (state->enabled[selection - 1] == 0)
        category = 19;
    palette = func_080CB9CC(category);
    /* An addition, as in the ROM: adds r0, #0xf9 at 0x0804FE6E (0xF9 is
     * -7 as a byte); every subtraction of 7 compiles to subs #7. */
    if (y != 0 && category == 19)
        palette += -7;

    /* The ROM lays the case blocks out as 16, 18, 17, 6, default
     * (0x0804FEC4, FEC8, FECE, FED4, FEDA); case 15 has no block. */
    tile = 0xE0;
    switch (category) {
    case 15:
        break;
    case 16:
        tile += 4;
        break;
    case 18:
        tile += 12;
        break;
    case 17:
        tile += 8;
        break;
    case 6:
        tile += 16;
        break;
    default:
        tile += 20;
        break;
    }

    tiles = menu->row + func_080161A0(x, y, menu->stride);
    tiles[0] = tile++ | (palette << 12);
    tiles[1] = tile++ | (palette << 12);
    tiles += menu->width;
    tiles[0] = tile++ | (palette << 12);
    /* Every tile is a post-increment, the last one dead, as in
     * src/0804FBB0.c: the ROM keeps the fourth tile in r0 (0x0804FF24-
     * 0x0804FF30), where the first two increments go back to r5. */
    tiles[1] = tile++ | (palette << 12);
    return category == 19;
}
