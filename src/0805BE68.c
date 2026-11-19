#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u16 *source;
    u8 unknown_10[5];
    u8 rows;
    u8 columns;
    u8 unknown_17[3];
    u16 position;
    u8 unknown_1C[4];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls;

typedef struct {
    u16 value;
    u8 field_02;
    u8 unknown_03;
} MenuEntry;

typedef struct {
    u8 unknown_0000[0xCF4];
    u8 window[0x2C];
    MenuList list;
    MenuControls controls;
    u8 unknown_0D54[0xD68 - 0xD54];
    u8 content[0x1BB8 - 0xD68];
    u16 count;
    u8 selected;
    u8 unknown_1BBB[0x2CA4 - 0x1BBB];
    MenuEntry entries[256];
} MenuState;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} GraphicsState;

typedef void (*MenuCallback)(void *);
extern MenuState *data_0200F428;
extern GraphicsState data_030008B0;
extern u8 data_0600C000[];
extern u16 func_080CC7F8(MenuEntry *output, u8 selector);
extern void func_0814186C(const void *, void *, u32);
extern void func_08016210(void *, const void *, u16, u16);
extern void func_0805C220(MenuList *, u16, u8, u32, u32);
extern void func_08015D58(void *, MenuCallback, MenuCallback);
extern void func_08017E80(void *);
extern void func_08017FB0(MenuControls *controls, u8 row);
extern void func_0805C02C(void *window);
extern void func_0805C09C(void);
extern void func_0802B108(MenuList *);

/* Complete target: [0x0805BE68, 0x0805BFC0), 344 bytes, 136 instructions.
 * f0b557464e464546e0b482b00006000e81460906090e8a461d4e30681d494018052170f0
 * b5fc32681b4b9846d11800230880d2200001171801a80380f9687a7db87d424352008020
 * 4004024301a8e5f0d9fc336811495d18114a9c18114801691148401a002800da1f30c202
 * 120c414658180388281c211cbaf796f94a467a83306840440088042810d80006000e0ee0
 * 28f40002a42c0000b81b0000f40c0000680d0000b008000300c000060420061c0023bd7e
 * b3421cda214802682d062d16a80012181f49501801881f48121812781c06241600200090
 * 381c231c00f06cf90134240601352d062d0e230e2416b442e2db134d2868154e80191549
 * 0022b9f7f7fe2868d424240100195146bcf71cf82868801900f056f800f08cf8381ccff7
 * bff828680419617c0a4a8018017002b038bc9846a146aa46f0bc01bc0047000028f40002
 * a42c0000a62c0000f40c0000817e0108ba1b0000
 */
void func_0805BE68(u8 position, u8 row)
{
    MenuList *list;
    u16 fill;
    u8 count;
    s8 i;
    s8 item;
    MenuControls *controls;

    data_0200F428->count = func_080CC7F8(data_0200F428->entries, 5);
    list = &data_0200F428->list;
    fill = 0;
    func_0814186C(&fill, list->source,
                  0x01000000 | (list->rows * list->columns * 2));
    func_08016210(data_0200F428->window, data_0200F428->content,
                  (data_0600C000 - data_030008B0.tiles) / 32,
                  data_0200F428->count);
    list->position = position;
    count = data_0200F428->count <= 4 ? data_0200F428->count : 4;
    for (i = 0, item = list->position; i < count; i++, item++)
        func_0805C220(list, data_0200F428->entries[item].value,
                      data_0200F428->entries[item].field_02, i, 0);
    func_08015D58(data_0200F428->window, func_08017E80, 0);
    func_08017FB0(&data_0200F428->controls, row);
    func_0805C02C(data_0200F428->window);
    func_0805C09C();
    func_0802B108(list);
    /* The ROM forms base + 0xD40 at 0x0805BF8C and reads row with
     * ldrb #0x11 at 0x0805BF8E rather than one folded 0xD51 offset; merged
     * src/0805262C.c and src/0805BFC0.c read the row through the same local. */
    controls = &data_0200F428->controls;
    data_0200F428->selected = controls->row;
}
