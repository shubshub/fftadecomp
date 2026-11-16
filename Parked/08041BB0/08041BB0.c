#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    const u8 *text;
    u8 unknown_0c[2];
    u8 type;
    u8 value_0f;
    u8 value_10;
    u8 unknown_11[3];
} TextEntry08041BB0;

typedef struct {
    u8 unknown_00[0x18];
    TextEntry08041BB0 *entries;
} TextList08041BB0;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
    u8 unknown_14[0x1c];
    u16 id;
    u8 unknown_32[0x46];
    u8 list[0x48];
    u8 unknown_c0[8];
    TextList08041BB0 *text;
} Record08041BB0;

typedef struct {
    u8 unknown_000[0x954];
    Record08041BB0 records[1];
    u8 unknown_a20[0x22c];
    u8 text_state[1];
} State08041BB0;

typedef struct {
    u8 unknown_00[0x4a];
    s8 width;
    u8 unknown_4b;
} Unit08041BB0;

extern State08041BB0 *g_state_03002810;
extern Unit08041BB0 data_030009E0[];
extern u8 data_02003CB0[];
extern const u8 *const g_table_085567F0[];
extern u16 func_08017B68(void *, u32);
extern u16 func_08037F40(void *, s8, u16);
extern void func_08141868(const void *, void *, u32);
extern void func_08015110(void *, void *, const u8 *, u32, u32);
extern void func_080142DC(u8 *, u32, u32);
extern void func_08041848(u32, u16, u8 *, TextList08041BB0 *, void *);
extern void func_080418B4(u16, void *);
extern void func_08041988(u16, void *, u16, u32);

/* Complete [0x08041BB0, 0x08041FB4): 1028 bytes, 514 instructions. */
void func_08041BB0(s32 slot, s16 row, void *map)
{
    u8 *buffer = data_02003CB0;
    TextList08041BB0 *text = g_state_03002810->records[slot].text;
    u16 unit = g_state_03002810->records[slot].id;
    u16 width = data_030009E0[unit].width;
    u16 offset = func_08037F40(g_state_03002810->records[slot].list, (s8)row, width);
    u8 *tiles = g_state_03002810->records[slot].tiles + (offset << 5);
    u32 fill = 0;
    u16 selected;
    const u8 *string;
    u8 number;

    func_08141868(&fill, tiles, (width << 4) | 0x01000000);
    selected = func_08017B68(g_state_03002810->records[slot].list, (s8)row);
    switch (text->entries[selected].type) {
    case 0:
        string = text->entries[selected].text;
        func_08015110(g_state_03002810->text_state, tiles, string, 0, 1);
        func_080418B4(selected, map);
        break;
    case 1:
        func_08041848(6, selected, tiles, text, map);
        func_08041988(selected, map, 0xD000, 1);
        number = text->entries[selected].value_10;
        if (number < 0xFF) {
            func_080142DC(buffer, number, 2);
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          buffer, 0, 1);
        } else {
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          g_table_085567F0[0], 0, 1);
        }
        break;
    case 2:
        /* The ROM keeps cases 1 and 2 as two identical bodies with their own
           table entries (0x08041CE0, 0x08041D3C). */
        func_08041848(6, selected, tiles, text, map);
        func_08041988(selected, map, 0xD000, 1);
        number = text->entries[selected].value_10;
        if (number < 0xFF) {
            func_080142DC(buffer, number, 2);
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          buffer, 0, 1);
        } else {
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          g_table_085567F0[0], 0, 1);
        }
        break;
    case 3:
        func_08041848(1, selected, tiles, text, map);
        func_08041988(selected, map, 0xE000, 0);
        break;
    case 4:
        func_08041848(0, selected, tiles, text, map);
        func_08041988(selected, map, 0xD000, 0);
        break;
    case 5:
        func_08041848(2, selected, tiles, text, map);
        func_08041988(selected, map, 0xD000, 0);
        break;
    case 6:
        func_08041848(4, selected, tiles, text, map);
        func_08041988(selected, map, 0xD000, 0);
        break;
    case 7:
        func_08041848(3, selected, tiles, text, map);
        func_08041988(selected, map, 0xE000, 0);
        break;
    case 9:
        func_08041848(0x10, selected, tiles, text, map);
        func_08041988(selected, map, 0xD000, 1);
        number = text->entries[selected].value_0f;
        if (number < 0xFF) {
            func_080142DC(buffer, number, 2);
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          buffer, 0, 1);
        } else {
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          g_table_085567F0[0], 0, 1);
        }
        break;
    case 8:
        func_08041848(0xF, selected, tiles, text, map);
        func_08041988(selected, map, 0xD000, 1);
        number = text->entries[selected].value_0f;
        if (number < 0xFF) {
            func_080142DC(buffer, number, 2);
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          buffer, 0, 1);
        } else {
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          g_table_085567F0[0], 0, 1);
        }
        break;
    case 11:
        func_08041848(0x12, selected, tiles, text, map);
        func_08041988(selected, map, 0xD000, 1);
        number = text->entries[selected].value_0f;
        if (number < 0xFF) {
            func_080142DC(buffer, number, 2);
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          buffer, 0, 1);
        } else {
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          g_table_085567F0[0], 0, 1);
        }
        break;
    case 10:
        func_08041848(0x11, selected, tiles, text, map);
        func_08041988(selected, map, 0xD000, 1);
        number = text->entries[selected].value_0f;
        if (number < 0xFF) {
            func_080142DC(buffer, number, 2);
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          buffer, 0, 1);
        } else {
            func_08015110(g_state_03002810->text_state, tiles + 0x380,
                          g_table_085567F0[0], 0, 1);
        }
        break;
    case 12:
        func_08041848(5, selected, tiles, text, map);
        func_08041988(selected, map, 0xE000, 0);
        break;
    }
}
