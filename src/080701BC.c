#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u8 stride;
    u8 unknown_0D[7];
    u16 *tiles;
} TileMap;

extern u32 func_080CBA14(u8 index);
extern void func_080CB9E0(void *destination, u32 index);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0802ACA0(u16 *entries, u16 first, u8 palette, u16 count);

/* 0x080701BC..0x08070260. Each graphics tile is 32 bytes. */
void func_080701BC(TileMap *map, void *graphics, u32 graphic, u8 keep_palette, u8 x, u8 y)
{
    u32 icon[64];
    u16 first;
    u32 index = (u8)graphic;
    u8 palette = func_080CBA14(index);

    if (!keep_palette)
        palette -= 6;
    func_080CB9E0(icon, index);
    func_0814186C(icon, graphics, 0x80);
    first = ((u32)graphics - 0x06008000) >> 5;
    func_0802ACA0(map->tiles + (y * map->stride + x), first, palette, 4);
    func_0802ACA0(map->tiles + (map->stride * (y + 1) + x), first + 4, palette, 4);
}
