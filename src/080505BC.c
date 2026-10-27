#include "ffta.h"

/* Target: complete [0x080505BC, 0x0805064C), 144 bytes. */
typedef struct {
    u8 unknown_00[0x15];
    u8 height;
    u8 unknown_16[10];
} RowList;

typedef struct {
    u8 *root;
    u8 unknown_04[0x44];
    RowList list;
    u8 unknown_68[0x28];
    u8 *values;
} MenuState;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileState;

extern TileState data_030008B0;
extern u16 func_08017B9C(RowList *list, u32 row);
extern void func_08013A88(void *tiles, u32 rows);
extern u16 func_08017B68(RowList *list, u32 row);
extern const u8 *func_0805064C(MenuState *menu, s16 index);
extern u8 *func_08050734(MenuState *menu, u8 *tiles, u16 index);
extern void func_08015110(void *state, u8 *tiles, const u8 *text,
                          u32 style, u32 spacing);

void func_080505BC(MenuState *menu, u8 row)
{
    RowList *list = &menu->list;
    u32 style = 0;
    s8 signed_row = (s8)row;
    u8 *tiles;
    u16 index;
    const u8 *text;

    tiles = data_030008B0.tiles + func_08017B9C(list, signed_row) * 32;
    func_08013A88(tiles, list->height << 1);
    index = func_08017B68(list, signed_row);
    if ((s8)menu->values[index] <= 0)
        style = 1;
    text = func_0805064C(menu, (s16)index);
    tiles = func_08050734(menu, tiles, index);
    func_08015110(menu->root + 0x14, tiles, text, style, 1);
}
