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
    u8 unknown_00[0x1184];
    u8 field_1184[1];
} RootState;

extern TileState data_03000990;
extern RootState *data_0200F428;
extern u16 func_08017B9C(RowList *list, u32 index);
extern void func_08013A88(void *destination, u32 rows);
extern void func_08015110(void *state, void *tiles, const void *text,
                          u32 style, u32 spacing);

/* Complete [0x0805C3D4, 0x0805C434): 96 bytes, 39 reachable Thumb instructions.
 * 70b5464640b481b080460e1c111c1d1c2d062d0e09060916301cbbf7d5fb0d490004
 * c00a0c692418717d4900201cb7f741fb094800680949401801210091211c42462b1c
 * b8f77afe01b008bc984670bc01bc00479009000328f4000284110000
 */
void func_0805C3D4(const void *text, RowList *list, s8 row, u8 style)
{
    u8 *tiles = data_03000990.tiles + func_08017B9C(list, row) * 32;

    func_08013A88(tiles, list->field_15 * 2);
    func_08015110(data_0200F428->field_1184, tiles, text, style, 1);
}
