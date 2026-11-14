#include "ffta.h"

// 0x080D6A34..0x080D6D0C: 728 bytes.
typedef struct {
    u8 width;
    u8 height;
    u8 unknown_02[2];
    u8 mode;
    u8 flags;
    u8 data[1];
} TilePattern;

extern void func_080D6798(u16 *destination, s16 x, s16 y, const u8 *data,
                          u8 width, u8 height, u16 base, u8 palette,
                          u8 flipX, u8 flipY, u8 flags);

void func_080D6A34(u16 *destination, const TilePattern *pattern, u16 base, u8 palette)
{
    u16 i;
    u16 j;

    switch (pattern->mode) {
    case 1:
        func_080D6798(destination, 0, 0, pattern->data, pattern->width, pattern->height,
                      base, palette, 0, 0, pattern->flags & 2);
        break;
    case 2:
        for (i = 0; i < 32; i += pattern->width) {
            func_080D6798(destination, i, 0, pattern->data, pattern->width, pattern->height,
                          base, palette, 0, 0, pattern->flags & 2);
        }
        break;
    case 3:
        for (i = 0; i < 32; i += pattern->height) {
            func_080D6798(destination, 0, i, pattern->data, pattern->width, pattern->height,
                          base, palette, 0, 0, pattern->flags & 2);
        }
        break;
    case 4:
        for (j = 0; j < 32; j += pattern->height) {
            for (i = 0; i < 32; i += pattern->width) {
                func_080D6798(destination, i, j, pattern->data, pattern->width,
                              pattern->height, base, palette, 0, 0, pattern->flags & 2);
            }
        }
        break;
    case 5:
        func_080D6798(destination, 0, 0, pattern->data, pattern->width, pattern->height,
                      base, palette, 0, 0, pattern->flags & 2);
        func_080D6798(destination, pattern->width, 0, pattern->data, pattern->width,
                      pattern->height, base, palette, 1, 0, pattern->flags & 2);
        break;
    case 6:
        func_080D6798(destination, 0, 0, pattern->data, pattern->width, pattern->height,
                      base, palette, 0, 0, pattern->flags & 2);
        func_080D6798(destination, 0, pattern->height, pattern->data, pattern->width,
                      pattern->height, base, palette, 0, 1, pattern->flags & 2);
        break;
    case 7:
        func_080D6798(destination, 0, 0, pattern->data, pattern->width, pattern->height,
                      base, palette, 0, 0, pattern->flags & 2);
        func_080D6798(destination, pattern->width, 0, pattern->data, pattern->width,
                      pattern->height, base, palette, 1, 0, pattern->flags & 2);
        func_080D6798(destination, 0, pattern->height, pattern->data, pattern->width,
                      pattern->height, base, palette, 0, 1, pattern->flags & 2);
        func_080D6798(destination, pattern->width, pattern->height, pattern->data,
                      pattern->width, pattern->height, base, palette, 1, 1, pattern->flags & 2);
        break;
    }
}
