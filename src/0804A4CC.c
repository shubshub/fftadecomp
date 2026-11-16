/* 0x0804A4CC..0x0804A6B0: complete 484-byte Thumb owner, 199 instructions
 * and the literal pools at 0x0804A590, 0x0804A5D4 and 0x0804A68C.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC8];
    void *panel;
} MenuRecord;

typedef struct {
    u8 unknown_00[0x90];
    u16 *first_resource;
    u16 *second_resource;
    u8 unknown_98[0x8BC];
    MenuRecord records[1];
} MenuContext;

typedef struct {
    u8 unknown_00[0x18];
    u16 *tiles;
} TileStorage;

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
extern TileWindow *func_0808A268(u32 index, u8 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u16 *first_output, u16 *second_output, u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_08016344(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern void func_0808AA18(u32 index);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern void func_08037C84(u32 slot, void *resource, u32 renderer, u32 column,
                         u32 row, u8 mode, u32 kind, u32 enabled);

void func_0804A4CC(u32 index, u32 selection)
{
    u8 *text = data_02003CB0;

    func_0808A268(6, 12, g_state_03002810->second_resource,
        g_state_03002810->first_resource, data_03002740.tiles,
        data_03002740.tiles + 0xE1, 0, 0, 16, 5, 15, 15,
        16, 5, 15, 15, 15, 15);
    func_08016344(data_030009E0[6].second_plane + 1,
        data_030009E0[6].width - 2, data_030009E0[6].height, 0xC0,
        data_030009E0[6].width, 5, 12);
    func_08016560(data_030009E0[6].first_plane + 1, 13, 15, 0xC0, 15, 1, 12);
    func_0808AA18(6);
    if (selection == 1) {
        func_08035678(0xC044, func_0808B8E4(6, 1, 2, 1),
                      func_08018524(text, 0x44, 15), 1);
    } else if (selection == 2) {
        func_08035678(0xC044, func_0808B8E4(6, 1, 2, 1),
                      func_08018524(text, 0x44, 16), 1);
    } else {
        func_08035678(0xC044, func_0808B8E4(6, 1, 2, 1),
                      func_08018524(text, 0x44, 10), 1);
    }
    data_030009E0[6].x = 16;
    data_030009E0[6].y = 5;
    /* The tile is assigned at the head of each of two member groups: with
     * source_width and source_height (the group func_0804A15C sets alone)
     * and with field_01 and field_48..field_4B (the group func_0808C16C
     * sets).  func_08049C24 has both groups with a call between them, so
     * both tile stores remain there.  Nothing separates them here: the
     * compiler drops the first store, and the ROM keeps its address, zero
     * and constant, formed at 0x0804A614..0x0804A61E ahead of the +0x2C
     * store.
     */
    data_030009E0[6].border_tile = 0x1AD;
    data_030009E0[6].source_width = 13;
    data_030009E0[6].source_height = 12;
    data_030009E0[6].border_tile = 0x1AD;
    data_030009E0[6].field_01 = 0;
    data_030009E0[6].field_48 = 1;
    data_030009E0[6].field_49 = 1;
    data_030009E0[6].field_4A = 13;
    data_030009E0[6].field_4B = 14;
    func_08037C84(index, g_state_03002810->records[index].panel,
                 6, 0, 0, 0, 11, 0);
}
