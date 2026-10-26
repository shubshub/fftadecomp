#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 *tiles;
    u8 unknown_1c[0x0c];
    u8 stride;
    u8 unknown_29[0x23];
} TileRenderer;

extern TileRenderer data_030009E0[];

void func_080892D8(u32 renderer_index, u16 tile, u16 attributes,
                   u8 x, u8 y, u8 width, u8 height)
{
    u16 value = tile | attributes;
    s32 row;
    s32 column;

    for (row = 0; row < height; row++) {
        u16 *destination = data_030009E0[renderer_index].tiles;
        destination += (row + y) * data_030009E0[renderer_index].stride + x;

        for (column = 0; column < width; column++) {
            destination[column] = value++;
        }
    }
}
