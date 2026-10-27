#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 height;
} RowList080535E8;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileState080535E8;

typedef struct {
    u8 unknown_00[0x1a60];
    u8 text_state[1];
} MenuState080535E8;

extern TileState080535E8 data_030008B0;
extern MenuState080535E8 *data_0200F428;

u16 func_08017B9C(RowList080535E8 *list, u32 index);
void func_08013A88(void *destination, u32 rows);
void func_08015110(void *state, void *tiles, void *text, u32 style, u32 spacing);

void func_080535E8(void *text, RowList080535E8 *list, s8 row, u8 style)
{
    u8 *tiles = data_030008B0.tiles + func_08017B9C(list, row) * 32;

    func_08013A88(tiles, list->height << 1);
    func_08015110(data_0200F428->text_state, tiles, text, style, 1);
}
