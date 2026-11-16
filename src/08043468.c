#include "ffta.h"

/* Byte 0 as src/0803D550.c declares it.  Byte 0x8E is a bit-field byte, as
 * src/08035174.c declares it for the same object (flag4_8e); bit 6 is set
 * the way flag_20 is (ldrb, movs #0x40, orrs into the loaded byte,
 * 0x0804377C; flag_20 at 0x080438FA). */
typedef struct {
    u8 unknown_00 : 5;
    u8 flag_20 : 1;
    u8 flag_40 : 1;
    u8 unknown_07 : 1;
    u8 unknown_01[0x8D];
    u8 unknown_8E_0 : 6;
    u8 flag_8E_40 : 1;
    u8 unknown_8E_7 : 1;
} MenuWindow08043468;

/* Laid out as src/0803D550.c declares it, with the cursor read as a u16 at
 * 0x10 (ldrh at 0x080436DC). */
typedef struct {
    u16 unknown_00;
    u8 result;
    u8 state;
    u8 unknown_04[10];
    u16 buttons;
    u16 selection;
    u8 unknown_12[0x86];
    void *source;
    u8 unknown_9c[0x30];
} MenuSlot08043468;

typedef struct {
    void *owner;
    MenuWindow08043468 *window;
    u8 unknown_008[0x78];
    u8 field_80;
    u8 unknown_081[0x0F];
    u16 *first_resource;
    u16 *second_resource;
    u8 unknown_098[0x4B8 - 0x98];
    u8 closed[6];
    u8 active[6];
    u8 unknown_4c4[0x984 - 0x4C4];
    MenuSlot08043468 slots[3];
    u8 unknown_be8[0xF3E - 0xBE8];
    u8 field_F3E;
} MenuContext08043468;

/* The 0x4C-byte renderer entry, as src/0803F6F8.c declares it. */
typedef struct {
    u8 busy;
    u8 field_01;
    u8 unknown_02[3];
    u8 status;
    u8 unknown_06[8];
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
} TileWindow08043468;

/* As src/08049C24.c declares it. */
typedef struct {
    u8 unknown_00[0x10];
    u16 *tiles;
} TileStorage08043468;

extern MenuContext08043468 *g_state_03002810;
extern TileWindow08043468 data_030009E0[];
extern TileStorage08043468 data_03002740;
extern u8 data_02003CB0[];
extern u8 data_0201F4E4;
extern u32 func_08043DF4(void *object, u32 value);
extern TileWindow08043468 *func_0808A268(u32 index, u8 mode,
    u16 *first_resource, u16 *second_resource, u16 *first_tiles,
    u16 *second_tiles, u16 *first_output, u16 *second_output,
    u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_08037C84(u32 index, void *panel, u32 renderer, u32 x,
                         u32 y, u32 row, u8 value, u32 enabled);
extern void func_08016344(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern u32 func_0808A604(u32 renderer, u16 command);
extern u32 func_08040388(u32 index, u16 mask);
extern void func_08141540(u16 song_id);
extern void func_08035844(u32 enabled);
extern void func_080C9574(u16 bit_index, u16 enabled);
extern void func_080359E4(s32 index, u8 value);
extern void func_080358B0(u32 enabled);

/* Complete [0x08043468, 0x0804393C): 1236 bytes, including literal pools. */
void func_08043468(u32 slot)
{
    switch (g_state_03002810->slots[slot].state) {
    case 0: {
        s32 offset;
        u8 x;
        u8 width;

        g_state_03002810->active[slot] = 0;
        g_state_03002810->window->flag_20 = 0;
        g_state_03002810->window->flag_40 = 0;
        /* 11 is set once here (0x080434F4, kept in r8) and reused for
         * both x arguments and the x store (0x08043530, 0x08043546,
         * 0x0804356A). */
        x = 11;
        width = 9;
        offset = (6 - func_08043DF4(g_state_03002810->slots[slot].source, 9)) * 2;
        func_0808A268(4, 12, g_state_03002810->second_resource,
            g_state_03002810->first_resource, data_03002740.tiles,
            data_03002740.tiles + 0xB4, 0, 0, x, 3, width, 15 - offset,
            x, 3, width, 15 - offset, width, 15 - offset);
        data_030009E0[4].x = x;
        data_030009E0[4].y = 3;
        data_030009E0[4].border_tile = 0xCB;
        data_030009E0[4].field_01 = 0;
        data_030009E0[4].field_48 = 1;
        data_030009E0[4].field_49 = 1;
        /* 7 is formed before its field address (0x08043598), as the
         * computed field_4B is (0x080435A2).  The siblings also store two
         * less than the width here: 12 for 14 in src/08049C24.c, 14 for 16
         * in src/0803F6F8.c. */
        data_030009E0[4].field_4A = width - 2;
        data_030009E0[4].field_4B = 12 - offset;
        func_08037C84(slot, g_state_03002810->slots[slot].source,
                      4, 0, 0, 0, 0x83, 1);
        func_08016344(data_030009E0[4].second_plane,
            data_030009E0[4].width, data_030009E0[4].height,
            0xC0, data_030009E0[4].width, 5, 12);
        func_08016560(data_030009E0[4].first_plane, width, 15 - offset,
                      0xC0, width, 1, 12);
        func_08035678(0xC03E, func_0808B8E4(4, 1, 1, 1),
                      func_08018524(data_02003CB0, 0x3E, 3), 1);
        data_030009E0[4].status = 3;
        func_0808A604(4, 11);
        data_0201F4E4 = 1;
        g_state_03002810->slots[slot].state = 0xFD;
        break;
    }
    case 1:
        if (func_08040388(slot, 0xFFFF) == 0xFF) {
            g_state_03002810->slots[slot].result = 6;
            g_state_03002810->slots[slot].state = 0xFF;
        } else if (g_state_03002810->slots[slot].buttons & 1) {
            if (g_state_03002810->slots[slot].selection == 0) {
                func_08141540(100);
                func_08035844(0);
                g_state_03002810->slots[slot].buttons = 0;
                g_state_03002810->field_80 = 0x16;
            } else if (g_state_03002810->slots[slot].selection == 1) {
                func_08141540(100);
                func_08035844(0);
                g_state_03002810->slots[slot].buttons = 0;
                g_state_03002810->field_80 = 0x15;
            } else if (g_state_03002810->slots[slot].selection == 2) {
                func_08141540(100);
                func_08035844(0);
                g_state_03002810->slots[slot].buttons = 0;
                func_080C9574(0x40, 1);
                g_state_03002810->field_80 = 0x14;
            } else if (g_state_03002810->slots[slot].selection == 3) {
                func_08035844(0);
                g_state_03002810->field_F3E = 0x1E;
                g_state_03002810->window->flag_8E_40 = 1;
                g_state_03002810->slots[slot].buttons = 0;
                func_0808A604(4, 1);
                data_0201F4E4 = 0xFE;
                g_state_03002810->slots[slot].state = 0xFD;
                break;
            } else if (g_state_03002810->slots[slot].selection == 4) {
                func_08141540(100);
                data_030009E0[4].status = 3;
                func_0808A604(4, 12);
                g_state_03002810->slots[slot].state = 3;
                break;
            }
            func_0808A604(4, 1);
            data_0201F4E4 = 0xFF;
            g_state_03002810->slots[slot].state = 0xFD;
        } else if (g_state_03002810->slots[slot].buttons & 2) {
            func_08141540(105);
            data_030009E0[4].status = 3;
            func_0808A604(4, 12);
            data_0201F4E4 = 0xFF;
            g_state_03002810->slots[slot].state = 0xFD;
        } else if (g_state_03002810->slots[slot].result == 3) {
            func_0808A604(4, 2);
        }
        break;
    case 3:
        if (!data_030009E0[4].busy) {
            func_080359E4(1, 2);
            g_state_03002810->slots[slot].state = 2;
            g_state_03002810->slots[slot].buttons = 0;
        }
        break;
    case 2:
        if (g_state_03002810->slots[1].state == 0xFE)
            g_state_03002810->slots[slot].state = 0xFE;
        else if (g_state_03002810->slots[1].state == 0xFF)
            g_state_03002810->slots[slot].state = 1;
        break;
    case 0xFD:
        if (!data_030009E0[4].busy)
            g_state_03002810->slots[slot].state = data_0201F4E4;
        break;
    case 0xFF:
        g_state_03002810->window->flag_20 = 1;
        g_state_03002810->window->flag_40 = 1;
        func_080358B0(1);
        /* fall through: 0x08043912 runs on into the 0xFE block. */
    case 0xFE:
        g_state_03002810->closed[slot] = 0;
        break;
    }
}
