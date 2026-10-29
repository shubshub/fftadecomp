#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
    u16 *tiles;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} Tilemap08089400;

extern Tilemap08089400 data_030009E0[];

/* Complete [0x08089400, 0x080894AC): 172 bytes, 82 instructions. */
void func_08089400(u32 index, u16 tile_offset, u8 x, u8 y,
                   u8 width, u8 height)
{
    u16 *destination = data_030009E0[index].tiles;
    u16 tile;
    s32 row;
    s32 column;
    s32 offset;

    destination += data_030009E0[index].stride * y + x;
    tile = *destination & 0xFFF;

    for (row = 0; row < height; row++) {
        destination = data_030009E0[index].tiles;
        offset = row + y;
        destination += data_030009E0[index].stride * offset + x;
        for (column = 0; column < width; column++)
            destination[column] = tile++ + tile_offset;
    }
}
