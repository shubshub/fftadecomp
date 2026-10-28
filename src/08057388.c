#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 height;
} RowList;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileState;

typedef struct {
    u8 unknown_00[0x19C8];
    u8 text_state[1];
} MenuState;

extern TileState data_030008B0;
extern MenuState *data_0200F428;
extern u16 func_08017B9C(RowList *list, u32 index);
extern void func_08013A88(void *destination, u32 rows);
extern void func_08015110(void *state, void *tiles, const void *text,
                          u32 style, u32 spacing);

/* Complete [0x08057388, 0x080573E8): 96 bytes, 39 reachable Thumb instructions. */
void func_08057388(const void *text, RowList *list, s8 row, u8 style)
{
    u8 *tiles = data_030008B0.tiles + func_08017B9C(list, row) * 32;

    func_08013A88(tiles, list->height * 2);
    func_08015110(data_0200F428->text_state, tiles, text, style, 1);
}
