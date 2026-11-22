/* 0x0803D3DC..0x0803D550: complete 372-byte Thumb owner, 157 instructions
 * and the literal pools at 0x0803D3F8 and 0x0803D528.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x90];
    u16 *first_resource;
    u16 *second_resource;
} MenuContext;

typedef struct {
    u8 unknown_00[0x10];
    u16 *tiles;
} TileStorage;

/* The 0x4C-byte renderer entry, as src/0804A4CC.c declares it. */
typedef struct {
    u8 unknown_00;
    u8 field_01;
    u8 unknown_02[0xC];
    u16 border_tile;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2A[2];
    u8 source_width;
    u8 source_height;
    u8 unknown_2E[6];
    u8 x;
    u8 y;
    u8 unknown_36[0x12];
    u8 field_48;
    u8 field_49;
    u8 field_4A;
    u8 field_4B;
} TileWindow;

extern u8 data_02003CB0[];
extern MenuContext *g_state_03002810;
extern TileStorage data_03002740;
extern TileWindow data_030009E0[];
extern u8 data_06009960[];
extern TileWindow *func_0808A268(u32 index, u8 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u16 *first_output, u16 *second_output, u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08016344(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);

void func_0803D3DC(s32 count)
{
    u8 *text = data_02003CB0;
    s32 inset;
    u16 zero;

    if (count > 5)
        inset = 0;
    else
        inset = (6 - count) * 2;
    func_0808A268(4, 12, g_state_03002810->second_resource,
        g_state_03002810->first_resource, data_03002740.tiles,
        data_03002740.tiles + 0xD2, 0, 0, 8, 2, 14, 15 - inset,
        8, 2, 14, 15 - inset, 14, 15 - inset);
    data_030009E0[4].x = 8;
    data_030009E0[4].y = 2;
    /* The tile is assigned at the head of each of two member groups, as in
     * src/0804A4CC.c: with source_width and source_height (the group
     * src/08049C24.c sets with the window-4 tile 0xCB) and with field_01
     * and field_48..field_4B.  Nothing separates them, so the compiler
     * drops the first store; the ROM keeps its address and zero, formed
     * at 0x0803D466..0x0803D46C ahead of the +0x2C store, while 0xE3 is
     * formed only at the surviving store (0x0803D484).
     */
    data_030009E0[4].border_tile = 0xCB;
    data_030009E0[4].source_width = 12;
    data_030009E0[4].source_height = 12 - inset;
    data_030009E0[4].border_tile = 0xE3;
    data_030009E0[4].field_01 = 0;
    data_030009E0[4].field_48 = 1;
    data_030009E0[4].field_49 = 1;
    data_030009E0[4].field_4A = 12;
    data_030009E0[4].field_4B = 12 - inset;
    zero = 0;
    func_0814186C(&zero, data_06009960, 0x01001500);
    func_08016344(data_030009E0[4].second_plane,
        data_030009E0[4].width, data_030009E0[4].height,
        0xC0, data_030009E0[4].width, 5, 12);
    func_08016560(data_030009E0[4].first_plane,
        14, data_030009E0[4].height, 0xC0, 14, 1, 12);
    func_08035678(0xC03E, func_0808B8E4(4, 1, 1, 1),
        func_08018524(text, 0x3E, 10), 1);
}
