#include "ffta.h"

/* 0801B73C..0801B796: 90 bytes. */
struct Rectangle {
    u8 left;
    u8 unknown_01;
    u8 top;
    u8 unknown_03;
    s16 right;
    s16 bottom;
};

extern u16 *func_0801AD1C(u8 layer);

void func_0801B73C(const struct Rectangle *rectangle, u8 layer, u16 tile)
{
    u16 *map = func_0801AD1C(layer);
    u8 y;
    u8 x;

    for (y = rectangle->top; y < rectangle->bottom && y < 64; y++) {
        for (x = rectangle->left; x < rectangle->right && x < 64; x++)
            map[y * 64 + x] = tile;
    }
}
