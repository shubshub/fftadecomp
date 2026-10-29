#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
    u16 *tiles;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} Tilemap08089368;

extern Tilemap08089368 data_030009E0[];

/* Complete [0x08089368, 0x08089400): 152 bytes, 71 instructions. */
void func_08089368(u32 index, u16 attributes, u8 x, u8 y,
                   u8 width, u8 height)
{
    s32 row;
    s32 column;

    for (row = 0; row < height; row++) {
        u16 *destination = data_030009E0[index].tiles;
        destination += x + (row + y) * data_030009E0[index].stride;

        for (column = 0; column < width; column++)
            destination[column] = (destination[column] & 0x0FFF) + attributes;
    }
}
