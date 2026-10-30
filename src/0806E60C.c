#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 field_15;
    u8 unknown_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u16 field_1C;
} RowList;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileState;

typedef struct {
    u8 unknown_00[0x39F4];
    u8 field_39F4[1];
} RootState;

extern TileState data_03000990;
extern RootState *data_0200F428;
extern u16 func_08017B9C(RowList *list, u32 index);
extern void func_08013A88(void *destination, u32 rows);
extern void func_08015110(void *state, void *tiles, const void *text,
                          u32 style, u32 spacing);

/* Complete [0x0806E60C, 0x0806E66C): 96 bytes, 39 reachable Thumb instructions.
 * 70b5464640b481b080460e1c111c1d1c2d062d0e09060916301ca9f7b9fa0d49
 * 0004c00a0c692418717d4900201ca5f725fa094800680949401801210091211c
 * 42462b1ca6f75efd01b008bc984670bc01bc00479009000328f40002f4390000
 */
void func_0806E60C(const void *text, RowList *list, s8 row, u8 style)
{
    u8 *tiles = data_03000990.tiles + func_08017B9C(list, row) * 32;

    func_08013A88(tiles, list->field_15 * 2);
    func_08015110(data_0200F428->field_39F4, tiles, text, style, 1);
}
