#include "ffta.h"

/* One 27-byte row of g_table_08564670, laid out as src/080D0B48.c declares
 * bytes 0-2.  Bytes 3 and 4 hold a seven-bit message index that starts at
 * bit 5 of byte 3 (ldrb/lsrs #5, ldrb/ands #15/lsls #3 at 0x0803F78C). */
typedef struct {
    u8 name_index;
    u16 mode : 1;
    u16 unknown_09 : 1;
    u16 type : 3;
    u16 value : 8;
    u16 unknown_15 : 3;
    u16 unknown_18 : 5;
    u16 message : 7;
    u16 unknown_24 : 4;
    u8 unknown_05[22];
} __attribute__((packed)) SelectionRecord0803F6F8;

typedef struct {
    u8 unknown_00[0xA8];
    u8 selector;
} Window0803F6F8;

/* Laid out as src/0803D550.c declares it. */
typedef struct {
    u16 unknown_00;
    u8 result;
    u8 state;
    u8 unknown_04[10];
    u16 buttons;
    u8 unknown_10[0x88];
    void *source;
    u8 unknown_9c[0x30];
} MenuSlot0803F6F8;

/* Three slots, as src/0803DE40.c declares them at 0x984: no more than three
 * 0xCC-byte slots fit below the text state at 0xC4C (src/080377E8.c). */
typedef struct {
    void *owner;
    Window0803F6F8 *window;
    u8 unknown_008[0x88];
    u16 *first_resource;
    u16 *second_resource;
    u8 unknown_098[0x4B8 - 0x98];
    u8 closed[6];
    u8 active[6];
    u8 unknown_4c4[0x984 - 0x4C4];
    MenuSlot0803F6F8 slots[3];
    u8 unknown_be8[0xC4C - 0xBE8];
    u8 text_state[1];
} MenuContext0803F6F8;

/* The 0x4C-byte renderer entry, merging the members src/08049C24.c and
 * src/0803D550.c name. */
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
} TileWindow0803F6F8;

extern MenuContext0803F6F8 *g_state_03002810;
extern TileWindow0803F6F8 data_030009E0[];
extern u8 *data_03002740[];
extern u8 data_0201F4E0;
extern u8 data_02003CB0[];
extern u8 data_0600B7E0[];
extern u8 data_0600B860[];
extern const SelectionRecord0803F6F8 g_table_08564670[];
extern const u8 *const g_table_08565F14[];
extern void func_0803F650(void *panel, u16 index);
extern TileWindow0803F6F8 *func_0808A268(u32 index, u8 mode,
    u16 *first_resource, u16 *second_resource, u8 *first_tiles,
    u8 *second_tiles, u16 *first_output, u16 *second_output,
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
extern void func_0808B950(u16 *destination, u16 tile, u16 width);
extern void func_0808B7C0(s32 index, u16 *destination, u16 tile,
                         u16 count, u16 flags);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_080CB9B0(void *object, u32 value);
extern void func_08015110(void *context, void *tiles, const void *text,
                          u32 mode, u32 spacing);
extern u32 func_0808A604(u32 renderer, u16 command);
extern u32 func_08040388(u32 index, u16 mask);
extern void func_08141540(u16 song_id);

/* Complete target: [0x0803F6F8, 0x0803FAA4), 940 bytes, 369 instructions. */
void func_0803F6F8(u32 index)
{
    switch (g_state_03002810->slots[index].state) {
    case 0:
        data_0201F4E0 = 0;
        g_state_03002810->slots[index].state = 4;
        break;
    case 4:
        if (data_0201F4E0++ > 30) {
            u8 *buffer = data_02003CB0;
            const SelectionRecord0803F6F8 *record;
            const u8 *name;
            u16 *map;
            u16 clear;
            u16 message;
            u16 palette;

            g_state_03002810->active[index] = 0;
            record = &g_table_08564670[g_state_03002810->window->selector];
            /* The ROM extracts the message (0x0803F78C) before it loads
             * the panel argument (0x0803F79A). */
            message = record->message;
            func_0803F650(g_state_03002810->slots[index].source, message);
            func_0808A268(6, 12, g_state_03002810->second_resource,
                g_state_03002810->first_resource, data_03002740[6],
                data_03002740[6] + 0x140, 0, 0, 13, 9, 16, 10, 13, 9, 16, 10,
                16, 10);
            data_030009E0[6].x = 13;
            data_030009E0[6].y = 9;
            data_030009E0[6].border_tile = 0x1DB;
            data_030009E0[6].field_01 = 0;
            data_030009E0[6].field_48 = 1;
            data_030009E0[6].field_49 = 4;
            data_030009E0[6].field_4A = 14;
            data_030009E0[6].field_4B = 6;
            func_08037C84(index, g_state_03002810->slots[index].source,
                          6, 0, 3, 0, 0x83, 1);
            func_08016344(data_030009E0[6].second_plane,
                data_030009E0[6].width, data_030009E0[6].height,
                0xC0, data_030009E0[6].width, 5, 12);
            func_08016560(data_030009E0[6].first_plane, 16, 10, 0xC0, 16, 1, 12);
            func_0808B950(func_0808B8E4(6, 1, 0, 4), 0xC050,
                          data_030009E0[6].width);
            func_0808B7C0(6, func_0808B8E4(6, 1, 1, 2), 0x1BF, 14, 0xC000);
            clear = 0;
            func_0814186C(&clear, data_0600B7E0, 0x01000200);
            /* 0xD000 is built once (0x0803F8D8) and ORed into each tile
             * number (0x0803F8E8-0x0803F90C), as src/080377E8.c does. */
            palette = 0xD000;
            map = func_0808B8E4(6, 1, 1, 2);
            map[0] = 0x1BF | palette;
            map[1] = 0x1C0 | palette;
            map[16] = 0x1C1 | palette;
            map[17] = 0x1C2 | palette;
            func_080CB9B0(buffer, 6);
            func_0814186C(buffer, data_0600B7E0, 0x40);
            /* The ROM loads the name (0x0803F920) before the text state
             * (0x0803F92A). */
            name = g_table_08565F14[record->name_index];
            func_08015110(g_state_03002810->text_state, data_0600B860,
                          name, 0, 1);
            data_030009E0[6].status = 1;
            func_0808A604(6, 11);
            data_0201F4E0 = 1;
            g_state_03002810->slots[index].state = 2;
        }
        break;
    case 1:
        if (func_08040388(index, 1) == 0xFF) {
            g_state_03002810->slots[index].state = 0xFF;
        } else if (g_state_03002810->slots[index].buttons & 1) {
            func_08141540(0x69);
            data_030009E0[6].status = 1;
            func_0808A604(6, 12);
            data_0201F4E0 = 0xFF;
            g_state_03002810->slots[index].state = 3;
        } else if (g_state_03002810->slots[index].result == 3) {
            func_0808A604(6, 2);
        }
        break;
    /* Cases 2 and 3 keep separate entry blocks (0x0803FA58, 0x0803FA68)
     * that join at 0x0803FA70. */
    case 2:
        if (!data_030009E0[6].busy)
            g_state_03002810->slots[index].state = data_0201F4E0;
        break;
    case 3:
        if (!data_030009E0[6].busy)
            g_state_03002810->slots[index].state = data_0201F4E0;
        break;
    case 0xFF:
        g_state_03002810->closed[index] = 0;
        break;
    }
}
