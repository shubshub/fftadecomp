#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 width;
    u8 height;
    u8 unknown_17[5];
    u16 tile;
} TileRun;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} GraphicsState;

extern GraphicsState data_030008B0;
extern const u8 *const g_table_08526680[];

extern void func_080CB980(void *buffer, u32 graphic);
extern u16 func_08017B68(TileRun *run, u32 row);
extern void func_08013A88(void *tiles, u16 count);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u16 func_08015110(void *text, void *tiles, const u8 *name, u8 style, u8 mode);

void func_08054314(TileRun *run, void *text, u16 row, u16 entry, u8 style)
{
    u32 icon[32];
    u16 offset;
    u8 *tiles;
    u16 name;

    if (entry > 85)
        func_080CB980(icon, 394);
    else
        func_080CB980(icon, 393);
    offset = func_08017B68(run, (s8)row);
    offset = (offset % (run->height + 1)) * run->width * 2;
    tiles = data_030008B0.tiles + (run->tile + offset) * 32;
    func_08013A88(tiles + 128, (run->width - 2) * 2);
    func_0814186C(icon, tiles, 64);
    name = entry > 85 ? entry - 85 : entry;
    func_08015110(text, tiles + 128, g_table_08526680[name + 625], style, 1);
}
