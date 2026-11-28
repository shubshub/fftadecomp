#include "ffta.h"

/* Complete target: [0x0803AE80, 0x0803BAE6), 3174 bytes, 1209 reachable
 * instructions.
 * The slot state machine of menu runner 3 (src/08034E88.c), written as its
 * sibling src/0803BAE8.c is: a compare tree over eleven case values, the
 * bodies laid out in source order. */

/* The 16-byte item as src/080D1218.c declares it: the id is read a byte at
 * a time (0x0803B5A8-0x0803B5B2). */
typedef struct {
    u16 id : 10;
    u16 countdown : 8;
    u8 status : 3;
    u8 unknown_15 : 3;
    u8 unknown_03;
    u8 unknown_04[2];
    u16 field_06;
    u16 unknown_08;
    u16 unknown_0A;
    u16 unknown_0C;
    u16 unknown_0E;
} __attribute__((packed)) Item;

/* One 0x46-byte row as src/080D1218.c declares it. */
typedef struct {
    u8 unknown_00[0x45];
    u8 unknown_45;
} __attribute__((packed)) ItemMetadata;

/* Bits 5 and 6 as src/0803BAE8.c declares them; bits 7-8 are a two-bit
 * field written with a halfword access (0x0803B5CE-0x0803B5DC). */
typedef struct {
    u16 unknown_00 : 5;
    u16 flag_20 : 1;
    u16 flag_40 : 1;
    u16 mode : 2;
    u16 unknown_09 : 7;
    u8 unknown_02[0x18];
    u8 field_1A;
    u8 field_1B;
    u8 field_1C;
    u8 name;
    u8 unknown_1E[2];
    u16 item_id;
    u16 cursor;
    Item *items[16];
    u8 unknown_64[2];
    u8 field_66;
    u8 unknown_67[0x27];
    u8 unknown_8E_0 : 3;
    u8 flag_8E_08 : 1;
    u8 unknown_8E_4 : 4;
    u8 unknown_8F[0x15];
    u16 field_A4;
    u8 unknown_A6[3];
    u8 field_A9;
} MenuWindow0803AE80;

/* Laid out as src/0803BAE8.c declares it. */
typedef struct {
    u16 unknown_00;
    u8 result;
    u8 state;
    u8 unknown_04[10];
    u16 buttons;
    u16 selection;
    u16 kind;
    u16 field_14;
    u16 field_16;
    u8 unknown_18[0x80];
    void *source;
    u8 unknown_9c[0x30];
} MenuSlot0803AE80;

typedef struct {
    void *owner;
    MenuWindow0803AE80 *window;
    u8 unknown_008[0x78];
    u8 field_80;
    u8 unknown_081[0x0F];
    u16 *first_resource;
    u16 *second_resource;
    u8 unknown_098[0x4B8 - 0x98];
    u8 closed[6];
    u8 active[6];
    u8 unknown_4c4[0x7E9 - 0x4C4];
    u8 field_7E9 : 4;
    u8 unknown_7E9 : 4;
    u8 unknown_7ea[0x984 - 0x7EA];
    MenuSlot0803AE80 slots[3];
    u8 unknown_be8[0xC4C - 0xBE8];
    u8 text_state[1];
} MenuContext0803AE80;

/* The 0x4C-byte renderer entry, as src/0803BAE8.c declares it. */
typedef struct {
    u8 busy;
    u8 field_01;
    u8 mode : 3;
    u8 unknown_02 : 4;
    u8 visible : 1;
    u8 unknown_03[2];
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
} TileWindow0803AE80;

/* As src/0803BAE8.c declares it. */
typedef struct {
    u8 unknown_00[0x10];
    u16 *tiles;
} TileStorage0803AE80;

/* As src/0803BAE8.c declares it. */
typedef struct {
    u32 unknown_00;
    u8 *entries;
} Display0803AE80;

/* As src/080230BC.c declares it. */
typedef struct {
    u8 unknown_0000[0x3C28];
    u16 field_3C28;
    u8 field_3C2A;
} State0803AE80;

/* The 12-byte record as src/0800A040.c declares it. */
typedef struct {
    u8 unknown_00;
    u8 field_01;
    u16 field_02;
    u16 field_04;
    u8 unknown_06[6];
} Record0803AE80;

extern MenuContext0803AE80 *g_state_03002810;
extern TileWindow0803AE80 data_030009E0[];
extern TileStorage0803AE80 data_03002740;
extern Display0803AE80 data_03000E30;
extern State0803AE80 g_state_02000000;
extern u8 data_02003CB0[];
extern u8 data_0201F47C;
extern u8 data_0201F47D;
extern u8 data_0201F47E;
extern u8 data_0201F47F;
extern u8 data_06009960[];
extern u8 data_060099E0[];
extern const u8 *const g_table_08526680[];
extern const ItemMetadata g_table_0855AE4C[];
extern Record0803AE80 g_table_08563A70[];

extern u8 func_080D1218(Item **output, u32 capacity, u32 category);
extern s32 func_0803D034(void *list, u8 *result);
extern TileWindow0803AE80 *func_0808A268(u32 index, u8 mode,
    u16 *first_resource, u16 *second_resource, u16 *first_tiles,
    u16 *second_tiles, u16 *first_output, u16 *second_output,
    u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08037C84(u32 slot, void *resource, u32 renderer, u32 column,
                         u32 row, u8 mode, u32 kind, u32 enabled);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B950(u16 *destination, u16 tile, u16 width);
extern void func_08016344(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern void func_08141540(u16 song_id);
extern void func_08015110(void *context, void *tiles, const void *text,
                          u32 mode, u32 spacing);
extern void func_0808B7C0(s32 index, u16 *destination, u16 tile,
                         u16 count, u16 flags);
extern void func_0808B858(s32 index, u16 *destination, u16 tile, u16 count);
extern u32 func_0808A604(u32 renderer, u16 command);
extern void func_0804C7A0(void *entries, u16 index);
extern void func_08042148(s32 slot);
extern void func_080372FC(u32 x, u32 y, u8 choice, u8 slot);
extern void func_080359E4(s32 index, u8 value);
extern u32 func_080421A4(u32 index);
extern void func_080358B0(u32 enabled);
extern void func_08035844(u32 enabled);
extern void func_081416DC(u16 value);
extern void func_0800A040(Record0803AE80 *record);

void func_0803AE80(u32 index)
{
    /* The sprite slot func_080372FC draws the icon in (cases 1 and 6); it
     * only ever holds 0.  The ROM keeps it as a separate zero: case 1 sets it
     * right after the tile clear, at 0x0803B1F0 (movs r4,#0), the buttons
     * reset at 0x0803B26C stores that same register, and the clear value uses
     * its own zero (0x0803B1E4).  agbcc keeps the two zeros apart only when
     * the variable is used again later in the function (case 6).  A literal 0,
     * as src/0803BAE8.c passes, or a variable scoped to case 1 merges them. */
    u8 icon_slot;

    switch (g_state_03002810->slots[index].state) {
    case 0: {
        /* As in src/0803BAE8.c, the buffer address is loaded again at each
         * use (0x0803B136, 0x0803B164). */
        u8 *buffer = data_02003CB0;
        s32 i;
        const u8 *text;
        u16 clear;

        for (i = 0; i < 16; i++)
            g_state_03002810->window->items[i] = 0;
        func_080D1218(g_state_03002810->window->items, 16,
                      g_state_03002810->window->name);
        if (!func_0803D034(g_state_03002810->slots[index].source,
                           &data_0201F47F)) {
            if (!g_state_03002810->window->flag_8E_08)
                func_08141540(0x6A);
            g_state_03002810->slots[index].state = 8;
            break;
        }
        func_08035844(0);
        func_08141540(100);
        data_030009E0[4].visible = 0;
        g_state_03002810->active[index] = 0;
        g_state_03002810->window->flag_20 = 0;
        g_state_03002810->window->flag_40 = 0;
        func_0808A268(4, 12, g_state_03002810->second_resource,
            g_state_03002810->first_resource, data_03002740.tiles,
            data_03002740.tiles + 0x134, 0, 0, 4, 2, 22, 14, 4, 2, 22, 14,
            22, 14);
        data_030009E0[4].x = 4;
        data_030009E0[4].y = 2;
        data_030009E0[4].border_tile = 0xEB;
        data_030009E0[4].field_01 = 0;
        data_030009E0[4].field_48 = 1;
        data_030009E0[4].field_49 = 1;
        data_030009E0[4].field_4A = 16;
        data_030009E0[4].field_4B = 7;
        clear = 0;
        func_0814186C(&clear, data_06009960, 0x01001400);
        /* The text is looked up before the first argument is formed
         * (0x0803B072-0x0803B088), so it is a local, as src/0803D290.c
         * writes the same draw. */
        text = g_table_08526680[g_state_03002810->window->name + 0x2CD];
        func_08015110(g_state_03002810->text_state, data_060099E0, text, 0, 1);
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, 2), 0xCB, 16, 0xC000);
        func_08037C84(index, g_state_03002810->slots[index].source,
                      4, 0, 0, 0, 0, 0);
        func_0808B950(func_0808B8E4(4, 1, 0, 4), 0xC050,
                      data_030009E0[4].width);
        func_08016344(data_030009E0[4].second_plane,
            data_030009E0[4].width, data_030009E0[4].height,
            0xC0, data_030009E0[4].width, 5, 12);
        func_08016560(data_030009E0[4].first_plane, 22, 14, 0xC0, 22, 1, 12);
        func_08035678(0xC03E, func_0808B8E4(4, 1, 1, 1),
                      func_08018524(buffer, 0x3E, 3), 1);
        if (data_0201F47F) {
            func_08035678(0xC044, func_0808B8E4(4, 1, 17, 1),
                          func_08018524(buffer, 0x44, 0x15), 1);
        }
        g_state_03002810->slots[index].state = 4;
        break;
    }
    case 1: {
        const u8 *text;
        u16 clear;

        clear = 0;
        func_0814186C(&clear, data_06009960, 0x01001400);
        icon_slot = 0;
        text = g_table_08526680[g_state_03002810->window->name + 0x2CD];
        func_08015110(g_state_03002810->text_state, data_060099E0, text, 0, 1);
        func_0808B858(4, func_0808B8E4(4, 1, 1, 2), 0, 0x14);
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, 2), 0xCB, 16, 0xC000);
        func_08042148(index);
        func_080372FC(0x26, 0x2F, g_state_03002810->window->name,
                      icon_slot);
        g_state_03002810->slots[index].buttons = 0;
        func_0808A604(4, 2);
        g_state_03002810->slots[index].state = 2;
        break;
    }
    case 2:
        data_030009E0[4].visible = 1;
        if (func_080421A4(index) == 0xFF) {
            data_030009E0[4].visible = 0;
            g_state_03002810->slots[index].result = 6;
            g_state_03002810->slots[index].state = 0xFF;
        } else if (g_state_03002810->slots[index].buttons & 1) {
            func_08141540(100);
            data_030009E0[4].visible = 0;
            switch (g_state_03002810->slots[index].kind) {
            case 3:
                g_state_03002810->slots[index].buttons = 0;
                g_state_03002810->field_80 = 0x14;
                g_state_03002810->slots[index].kind = 0;
                data_030009E0[4].status = 3;
                func_0808A604(4, 12);
                func_0804C7A0(data_03000E30.entries, 3);
                g_state_03002810->slots[index].state = 0xFD;
                break;
            case 4:
                g_state_03002810->slots[index].buttons = 0;
                g_state_03002810->field_80 = 0x10;
                g_state_03002810->slots[index].kind = 0;
                data_030009E0[4].status = 3;
                func_0808A604(4, 12);
                func_0804C7A0(data_03000E30.entries, 3);
                g_state_03002810->slots[index].state = 0xFD;
                break;
            case 5:
                g_state_03002810->slots[index].buttons = 0;
                g_state_03002810->field_80 = 0x13;
                g_state_03002810->slots[index].kind = 0;
                data_030009E0[4].status = 3;
                func_0808A604(4, 12);
                func_0804C7A0(data_03000E30.entries, 3);
                g_state_03002810->slots[index].state = 0xFD;
                break;
            case 6:
                g_state_03002810->slots[index].buttons = 0;
                g_state_03002810->field_80 = 0x11;
                g_state_03002810->slots[index].kind = 0;
                data_030009E0[4].status = 3;
                func_0808A604(4, 12);
                func_0804C7A0(data_03000E30.entries, 3);
                g_state_03002810->slots[index].state = 0xFD;
                break;
            case 7:
                g_state_03002810->slots[index].buttons = 0;
                g_state_03002810->field_80 = 0x12;
                g_state_03002810->slots[index].kind = 0;
                data_030009E0[4].status = 3;
                func_0808A604(4, 12);
                func_0804C7A0(data_03000E30.entries, 3);
                g_state_03002810->slots[index].state = 0xFD;
                break;
            case 9: {
                const ItemMetadata *metadata;
                s32 i;

                if (g_state_03002810->slots[index].field_14 == 0)
                    break;
                g_state_03002810->window->cursor =
                    g_state_03002810->slots[index].field_16;
                g_state_03002810->window->item_id =
                    g_state_03002810->window->items[g_state_03002810->window->cursor]->id;
                metadata = &g_table_0855AE4C[g_state_03002810->window->item_id];
                g_state_03002810->window->field_A9 = 2;
                g_state_03002810->window->mode = 2;
                func_081416DC(10);
                g_state_03002810->field_7E9 = 0;
                g_state_03002810->window->field_66 = 0;
                g_state_03002810->window->field_1C = g_state_03002810->window->field_1A;
                g_state_03002810->window->name = g_state_03002810->window->field_1B;
                g_state_03002810->window->field_A4 = metadata->unknown_45;
                g_state_02000000.field_3C28 = g_state_03002810->window->item_id;
                g_state_02000000.field_3C2A = metadata->unknown_45;
                func_0800A040(&g_table_08563A70[g_state_03002810->window->field_A4]);
                for (i = 0; i < 16; i++)
                    g_state_03002810->window->items[i] = 0;
                data_030009E0[4].status = 3;
                func_0808A604(4, 12);
                data_0201F47E = 150;
                g_state_03002810->slots[index].state = 5;
                break;
            }
            case 8:
                func_0804C7A0(data_03000E30.entries, 3);
                func_080359E4(1, 13);
                g_state_03002810->slots[index].state = 3;
                g_state_03002810->slots[index].buttons = 0;
                break;
            case 11:
                func_0804C7A0(data_03000E30.entries, 3);
                func_080359E4(1, 13);
                g_state_03002810->slots[index].state = 3;
                g_state_03002810->slots[index].buttons = 0;
                break;
            case 10: {
                const ItemMetadata *metadata;
                s32 i;

                g_state_03002810->window->cursor =
                    g_state_03002810->slots[index].field_16;
                g_state_03002810->window->item_id =
                    g_state_03002810->window->items[g_state_03002810->window->cursor]->id;
                metadata = &g_table_0855AE4C[g_state_03002810->window->item_id];
                g_state_03002810->window->field_A9 = 2;
                g_state_03002810->window->mode = 2;
                func_081416DC(10);
                g_state_03002810->field_7E9 = 0;
                g_state_03002810->window->field_66 = 0;
                g_state_03002810->window->field_1C = g_state_03002810->window->field_1A;
                g_state_03002810->window->name = g_state_03002810->window->field_1B;
                g_state_03002810->window->field_A4 = metadata->unknown_45;
                g_state_02000000.field_3C28 = g_state_03002810->window->item_id;
                g_state_02000000.field_3C2A = metadata->unknown_45;
                func_0800A040(&g_table_08563A70[g_state_03002810->window->field_A4]);
                for (i = 0; i < 16; i++)
                    g_state_03002810->window->items[i] = 0;
                data_030009E0[4].status = 3;
                func_0808A604(4, 12);
                data_0201F47E = 150;
                g_state_03002810->slots[index].state = 5;
                break;
            }
            case 12:
                func_0804C7A0(data_03000E30.entries, 3);
                g_state_03002810->slots[index].state = 0xFD;
                data_030009E0[4].status = 3;
                func_0808A604(4, 12);
                break;
            default:
                g_state_03002810->slots[index].kind = 0;
                g_state_03002810->slots[index].buttons = 0;
                break;
            }
        } else if (g_state_03002810->slots[index].buttons & 2) {
            data_030009E0[4].visible = 0;
            func_08141540(0x69);
            g_state_03002810->slots[index].kind = 0;
            func_0804C7A0(data_03000E30.entries, 3);
            g_state_03002810->slots[index].state = 0xFD;
            data_030009E0[4].status = 3;
            func_0808A604(4, 12);
        } else if (g_state_03002810->slots[index].result == 3) {
            func_0808A604(4, 2);
        }
        break;
    case 3:
        if (g_state_03002810->slots[1].state == 0xFF)
            g_state_03002810->slots[index].state = 1;
        break;
    case 5:
        /* The old value is tested after the decremented one is stored
         * (0x0803B95A-0x0803B966); an == test would be folded to a test
         * of the new value. */
        if (data_0201F47E-- <= 0) {
            g_state_03002810->field_80 = 0x18;
            g_state_03002810->slots[index].result = 6;
            g_state_03002810->slots[index].state = 0xFF;
        }
        break;
    case 4:
        if (func_080421A4(index) == 3) {
            data_030009E0[4].status = 3;
            func_0808A604(4, 11);
            data_0201F47C = 4;
            data_0201F47D = 2;
            g_state_03002810->slots[index].state = 6;
        }
        break;
    case 6:
        icon_slot = 0;
        if (!data_030009E0[data_0201F47C].busy) {
            func_080372FC(0x26, 0x30, g_state_03002810->window->name,
                          icon_slot);
            g_state_03002810->slots[index].state = data_0201F47D;
        }
        break;
    case 0xFD:
        if (!data_030009E0[4].busy)
            g_state_03002810->slots[index].state = 0xFF;
        break;
    case 0xFF:
        /* 3-11 leave the window as it is: blt to the default at 3, ble to
         * the exit at 11, then a test for 12 (0x0803BA42-0x0803BA4C). */
        switch (g_state_03002810->slots[index].kind) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            break;
        case 12:
            g_state_03002810->window->field_1C = g_state_03002810->window->field_1A;
            g_state_03002810->window->name = g_state_03002810->window->field_1B;
            func_08035844(0);
            func_080359E4(0, 6);
            break;
        default:
            g_state_03002810->window->flag_40 = 1;
            g_state_03002810->window->flag_20 = 1;
            func_080358B0(1);
            g_state_03002810->closed[index] = 0;
            break;
        }
        break;
    case 7:
        g_state_03002810->window->flag_40 = 1;
        g_state_03002810->window->flag_20 = 1;
        func_080358B0(1);
        g_state_03002810->closed[index] = 0;
        break;
    case 8:
        g_state_03002810->closed[index] = 0;
        break;
    }
}
