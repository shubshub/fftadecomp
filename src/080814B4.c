#include "ffta.h"

/* Complete target: [0x080814B4, 0x080817F8), 836 bytes, 347 instructions. */

typedef struct {
    u8 unknown_00[0xc];
    u16 *tiles;
    u8 unknown_10[5];
    u8 stride;
    u8 unknown_16;
    u8 divisor;
    u16 count;
    u16 position;
    u16 base;
    u8 unknown_1e[2];
} Menu080814B4;

typedef struct {
    u8 unknown_00[2];
    u16 flags;
    u16 icon;
    u8 unknown_06[8];
    u8 first;
    u8 second;
    u8 unknown_10[4];
} Entry080814B4;

typedef struct {
    u8 unknown_00[0x18];
    Entry080814B4 *entries;
} Object080814B4;

typedef struct {
    u8 unknown_00[0x10];
    u8 *vram;
    u8 unknown_14[0x1c];
    u16 window;
    u8 unknown_32[0x46];
    Menu080814B4 menu;
    u8 unknown_98[0x2c];
    const u8 **texts;
    Object080814B4 *object;
} Slot080814B4;

typedef struct {
    u8 unknown_0000[0x68c];
    u8 text_state[0x25fc];
    Slot080814B4 slots[1];
} State080814B4;

typedef struct {
    u8 unknown_00[0x4a];
    s8 width;
    s8 height;
} Window080814B4;

extern u8 data_02003CB0[];
extern State080814B4 *data_03002818;
extern Window080814B4 data_030009E0[];
extern const u8 data_08393C64[];
extern const u8 data_08393C67[];

extern u16 func_08017B68(Menu080814B4 *menu, u32 row);
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08015110(void *context, void *destination, const u8 *text,
                          u32 mode, u32 reset);
extern u8 func_080CB99C(u16 id);
extern void func_080CB980(void *buffer, u32 id);
extern void func_080142DC(void *buffer, u32 value, u32 digits);

/* The clamp, remainder and scale of func_08017B9C (src/08017B9C.c), with the
   window's width where that function reads the menu's own stride. */
static inline u16 row_offset(Menu080814B4 *menu, u32 row, u16 width)
{
    s16 value = (s8)row + menu->position;
    u32 base;

    if (value < 0)
        base = 0;
    else if (value > (s16)menu->count - 1)
        base = menu->count - 1;
    else
        base = (u16)value;
    return (u16)((u16)base % menu->divisor) * (width << 1) + menu->base;
}

void func_080814B4(u32 slot, u16 row, Menu080814B4 *menu)
{
    u8 *buffer = data_02003CB0;
    u16 index;
    u16 rows;
    const u8 **texts;
    Object080814B4 *object;
    u16 width;
    u16 id; /* the window's id, then the icon's */
    u32 flag;
    u8 *tiles;
    u16 attributes;
    u16 *out;
    u32 zero;
    const u8 *text;
    u8 number;

    object = data_03002818->slots[slot].object;
    texts = data_03002818->slots[slot].texts;
    id = data_03002818->slots[slot].window;
    width = data_030009E0[id].width;
    rows = data_030009E0[id].height >> 1;
    index = func_08017B68(&data_03002818->slots[slot].menu, (s8)row);
    if (object->entries[index].flags == 0)
        flag = 0;
    else
        flag = object->entries[index].flags & 1;
    tiles = data_03002818->slots[slot].vram
        + row_offset(&data_03002818->slots[slot].menu, (s8)row, width) * 32;
    zero = 0;
    func_08141868(&zero, tiles, (width << 4) | 0x01000000);
    text = texts[index];
    func_08015110(data_03002818->text_state, tiles + 0x80, text, flag, 1);
    id = object->entries[index].icon;
    attributes = (func_080CB99C(id) + 13) << 12;
    out = &menu->tiles[menu->stride * 2 * (index % rows)];
    out[0] = (out[0] & 0xfff) | attributes;
    out[1] = (out[1] & 0xfff) | attributes;
    out[menu->stride] = (out[menu->stride] & 0xfff) | attributes;
    out[menu->stride + 1] = (out[menu->stride + 1] & 0xfff) | attributes;
    if (menu->stride == 0x14) {
        out[0x13] = 0;
        out[menu->stride + 0x13] = 0;
    }
    func_080CB980(buffer, id);
    func_0814186C(buffer, tiles, 0x40);
    func_08015110(data_03002818->text_state, tiles + 0x400, data_08393C64, flag, 1);
    number = object->entries[index].first;
    if (number == 0xff) {
        func_08015110(data_03002818->text_state, tiles + 0x380, data_08393C67, flag, 1);
    } else if (number <= 9) {
        func_080142DC(buffer, number, 1);
        func_08015110(data_03002818->text_state, tiles + 0x3c0, buffer, flag, 1);
    } else {
        func_080142DC(buffer, number, 2);
        func_08015110(data_03002818->text_state, tiles + 0x380, buffer, flag, 1);
    }
    number = object->entries[index].second;
    if (number == 0xff) {
        func_08015110(data_03002818->text_state, tiles + 0x440, data_08393C67, flag, 1);
    } else if (number <= 9) {
        func_080142DC(buffer, number, 1);
        func_08015110(data_03002818->text_state, tiles + 0x480, buffer, flag, 1);
    } else {
        func_080142DC(buffer, number, 2);
        func_08015110(data_03002818->text_state, tiles + 0x440, buffer, flag, 1);
    }
}
