#include "ffta.h"

struct TileBlock0804018C {
    u8 unknown_00[0xC];
    u16 *destination;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16;
    u8 height;
    u8 unknown_18[4];
    u16 first_tile;
    u8 unknown_1E;
    u8 palette;
};

/* Complete [0x0804018C, 0x080401F2): 102 bytes, 51 instructions. */
void func_0804018C(struct TileBlock0804018C *block)
{
    u16 *destination = block->destination;
    u16 tile = (block->palette << 12) + block->first_tile;
    s32 width = block->width;
    u32 height = block->height;

    for (; height > 0; height--) {
        if (width != 0) {
            u16 *column = destination;
            s32 remaining = width;

            do {
                *column = tile++;
                column[block->width] = tile++;
                column++;
                remaining--;
            } while (remaining != 0);
        }
        destination += block->width * 2;
    }
}
