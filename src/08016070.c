#include "ffta.h"

/* Complete [0x08016070, 0x080161A0), 304 bytes: 145 instructions and the
 * literal words for data_030008B0 (0x080160F8) and data_02003CB0
 * (0x0801619C).  Draws the icon of an "@g" text command: it finds the text
 * cursor's character cell from its tile address, places a 2x2 block of tile
 * numbers in the window's tilemap and copies the icon's four tiles to the
 * cursor, then advances the cursor by 16 pixels.  Called from func_080120F0
 * (0x080127F8) and func_080154D8 (0x08015792). */

typedef struct {
    u8 unknown_00[4];
    u8 *destination;
} TextCursor;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
    u16 *tilemap;
} GraphicsState;

extern GraphicsState data_030008B0;
extern u8 data_02003CB0[];
extern u8 func_08015DAC(void *destination, u8 code, u8 *missing);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08013728(TextCursor *cursor, s16 amount);

void func_08016070(u8 code, TextCursor *cursor, void *graphics, u8 width,
                   u8 x, u8 y, u16 base, u16 flags)
{
    u8 missing = 0;
    /* The ROM copies the incoming pointer from r2 to sb at 0x080160AA,
     * between the missing-flag store and row = 0. */
    GraphicsState *display = graphics;
    u8 row = 0;
    u32 cells;
    u8 column;
    u8 top;
    u8 left;
    u16 tile;
    u16 *map;
    u8 palette;

    /* The difference and the shift are two operations on one register:
     * subs r1, r1, r0 at 0x080160BA, then lsrs r1, r1, #6. */
    cells = cursor->destination - (data_030008B0.tiles + base * 32);
    cells >>= 6;
    while (cells >= width) {
        cells -= width;
        row += 2;
    }
    column = cells;

    top = (flags & 0xC0) ? 2 : 1;
    if (flags & 0x20)
        left = (flags & 0x10) ? 3 : 8;
    else
        left = 1;
    if (code >= 0x81 && code <= 0x85)
        top++;

    tile = base + row * width + column * 2;
    map = &display->tilemap[(y + top + row) * 32 + (x + left + column)];
    palette = func_08015DAC(data_02003CB0, code, &missing);
    if (!missing) {
        tile += palette << 12;
        map[0] = tile++;
        map[1] = tile++;
        map[32] = tile++;
        map[33] = tile;
        func_0814186C(data_02003CB0, cursor->destination, 0x40);
    }
    func_08013728(cursor, 16);
}
