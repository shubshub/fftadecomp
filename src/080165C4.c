#include "ffta.h"

extern const s8 data_0836D634[][4];

// 0x080165C4 .. 0x080167FE: 570 bytes, including two literal pools.
// Draw one end of an eight-row frame.  When width > 4 the plain columns
// (4 .. width - 1 if flags & 0x10, else 0 .. width - 5) get border_tile on
// the first row, its vertical flip on the last and fill_tile in between.
// The shaped end columns come from the 4x4 offset table data_0836D634,
// rows 4..7 mirroring rows 3..0 with the vertical-flip bit: at the left
// end (flags & 0x10) with the horizontal-flip bit, otherwise mirrored at
// the right.  An entry of -1 is fill_tile; other negative entries leave
// the cell alone.
void func_080165C4(void *destination, u8 width, u8 height, u16 flags,
                   u8 stride, u16 border_tile, u16 fill_tile, u8 palette)
{
    u16 *buffer;
    u16 tile;
    u16 offset;
    u16 position;
    s32 first;
    s32 last;
    s32 y;
    s32 i;
    s32 x;

    if (height != 8)
        return;

    buffer = destination;
    if (width > 4) {
        offset = 0;
        if (flags & 0x10) {
            first = 4;
            last = width;
        } else {
            first = 0;
            last = width - 4;
        }
        for (y = 0; y < height; y++) {
            if (y == 0)
                tile = border_tile + (palette << 12);
            else if (y == height - 1)
                tile = border_tile + (palette << 12) + 0x800;
            else
                tile = fill_tile + (palette << 12);
            for (i = first; i < last; i++)
                (buffer + i)[offset] = tile;
            offset += stride;
        }
    }

    tile = border_tile + (palette << 12);
    if (flags & 0x10) {
        i = width;
        if (width > 4)
            i = 4;
        position = 0;
        tile += 0x400;
        for (y = 0; y < height; y++) {
            for (x = 0; x < i; x++) {
                s32 value;

                if (y <= 3)
                    value = data_0836D634[y][x];
                else
                    value = data_0836D634[height - 1 - y][x];
                if (value >= 0) {
                    s32 result = tile + value;

                    if (y > 3)
                        result += 0x800;
                    (buffer + position)[x] = result;
                } else if (value == -1) {
                    (buffer + position)[x] = fill_tile + (palette << 12);
                }
            }
            position += stride;
        }
    } else {
        if (width > 4) {
            i = 3;
            position = width - 4;
        } else {
            i = width - 1;
            position = 0;
        }
        for (y = 0; y < height; y++) {
            for (x = 0; x < i + 1; x++) {
                s32 value;

                if (y <= 3)
                    value = data_0836D634[y][x];
                else
                    value = data_0836D634[height - 1 - y][x];
                if (value >= 0) {
                    s32 result = tile + value;

                    if (y > 3)
                        result += 0x800;
                    (buffer + position)[i - x] = result;
                } else if (value == -1) {
                    (buffer + position)[i - x] = fill_tile + (palette << 12);
                }
            }
            position += stride;
        }
    }
}
