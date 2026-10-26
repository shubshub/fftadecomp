#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1c];
    u16 *tiles;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} Tilemap08089248;

extern Tilemap08089248 data_030009E0[];

/* 0x08089248..0x080892D8: 144 bytes, 70 instructions. */
void func_08089248(u32 index, u16 tile, u16 attributes,
                    u8 x, u8 y, u8 width, u8 height)
{
    s32 row;
    s32 column;
    s32 offset;
    u16 *destination;

    tile |= attributes;
    for (row = 0; row < height; row++) {
        destination = data_030009E0[index].tiles;
        offset = row + y;
        destination += data_030009E0[index].stride * offset + x;
        for (column = 0; column < width; column++)
            destination[column] = tile++;
    }
}
