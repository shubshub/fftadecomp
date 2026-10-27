#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u8 width;
    u8 unknown_0D[7];
    u16 *tiles;
} TileGrid0802B460;

void func_0802ACA0(u16 *entries, u16 first, u8 palette, u16 count);

void func_0802B460(TileGrid0802B460 *grid, u8 x, u8 y)
{
    func_0802ACA0(grid->tiles + (grid->width * y + x), 0x63, 0xD, 3);
    func_0802ACA0(grid->tiles + (grid->width * (y + 1) + x), 0x66, 0xD, 3);
}
