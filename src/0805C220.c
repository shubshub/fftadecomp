#include "ffta.h"

#include "item_quantity_menu.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} GraphicsState;

typedef struct {
    u16 name;
    u16 description;
    u8 unknown_04[4];
    u8 category;
    u8 unknown_09[0x17];
} ItemDefinition;

extern GraphicsState data_030008B0;
extern const ItemDefinition g_table_0851D180[];
extern const u8 *const g_table_08526680[];
extern void func_080CB980(void *output, u32 item);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u16 func_08015110(void *text_state, void *tiles, const u8 *string, u8 style, u8 spacing);
extern u16 func_080161BC(const u8 *string);
extern void func_08013A88(void *destination, u16 tiles);
extern void func_0802979C(void *text_state, void *tiles, u32 number, u32 digits, u32 style);
extern u8 func_080CB99C(u16 item);

static inline void render_name(void *context, u8 *tiles, u16 item, u8 style)
{
    u16 name_tiles;

    func_08015110(context, tiles + 128,
                  g_table_08526680[g_table_0851D180[item].name], style, 1);
    name_tiles = func_080161BC(g_table_08526680[g_table_0851D180[item].name]) + 2;
    func_08013A88(tiles + name_tiles * 64, (14 - name_tiles) * 2);
}

/* Complete [0x0805C220, 0x0805C340), 288 bytes and 124 instructions.
 * f0b557464e464546e0b4a3b0071c894698462b980904090c89461206120e219242461204
 * 120c904603061b0e229301a86ff096fb43461b0698461916381cbbf783fc061c3604360c
 * b97d0131301ce6f06ffb797d484340042c49000cba8b801840010d692d1801a8291c4022
 * e5f0eefa274b186827494018291c8031264a9246264a4b465c01a4182288920052441268
 * 01230093229bb8f72bff2088800050440068b9f77bff02300004000c8201aa180e21091a
 * 4904090c101cb7f7d5fb14490868144a8018e0239b00ed1822990091291c219a0223cdf7
 * 51fa4246120e90463606360e48466ff049fb031c0d331b061b0e381c4146321c00f012f8
 * 23b038bc9846a146aa46f0bc01bc0047b008000328f40002841100008066520880d15108
 */
void func_0805C220(MenuList *list, u16 item, u8 quantity, u32 row_arg, u32 style_arg)
{
    u16 row = row_arg;
    u8 style = style_arg;
    u32 icon[32];
    u16 selection, offset;
    u8 *tiles;

    func_080CB980(icon, item);
    selection = func_08017B68(list, (s8)row);
    offset = selection % (list->columns + 1) * list->rows * 2;
    tiles = data_030008B0.tiles + (list->first_tile + offset) * 32;
    func_0814186C(icon, tiles, 64);
    render_name(data_0200F428->content + (0x1184 - 0xD68), tiles, item, style);
    func_0802979C(data_0200F428->content + (0x1184 - 0xD68), tiles + 14 * 64, quantity, 2, style);
    func_0805C340(list, row, selection, func_080CB99C(item) + 13);
}
