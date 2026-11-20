#include "ffta.h"

/* Window text icon drawing, 0x08016070..0x080161A0 (304 bytes). */
typedef struct {
    u8 unknown_00[4];
    u8 *destination;
} TextCursor;

typedef struct {
    u8 unknown_00[0x14];
    u16 *tilemap;
} WindowMap;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics;

extern Graphics data_030008B0;
extern u8 data_02003CB0[];
extern u8 func_08015DAC(void *destination, u8 code, u8 *missing);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08013728(TextCursor *cursor, s16 advance);

void func_08016070(u8 code, TextCursor *cursor, WindowMap *window,
                   u8 width, u8 x, u8 y, u16 base_tile, u16 flags)
{
    u8 missing = 0;
    u8 row = 0;
    u16 icon_tile;
    u32 cells;
    u8 column;
    u8 top;
    u8 left;
    u16 *entry;
    u8 palette;

    icon_tile = base_tile;
    cells = ((u32)cursor->destination - (u32)(data_030008B0.tiles + icon_tile * 32)) >> 6;
    while (cells >= width) {
        cells -= width;
        row += 2;
    }
    column = cells;

    top = flags & 0xC0 ? 2 : 1;
    if (flags & 0x20)
        left = flags & 0x10 ? 3 : 8;
    else
        left = 1;
    if (code >= 0x81 && code <= 0x85)
        ++top;

    icon_tile = icon_tile + row * width + column * 2;
    entry = window->tilemap + ((y + row + top) * 32 + (x + left + column));

    palette = func_08015DAC(data_02003CB0, code, &missing);
    if (missing == 0) {
        u16 tile = icon_tile + (palette << 12);
        entry[0] = tile++;
        entry[1] = tile++;
        entry[32] = tile++;
        entry[33] = tile;
        func_0814186C(data_02003CB0, cursor->destination, 0x40);
    }
    func_08013728(cursor, 16);
}
