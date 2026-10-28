#include "ffta.h"

/* Complete [0x0806F5FC, 0x0806F67A): 126 bytes, 63 instructions. */
typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    const u16 *source;
    u8 unknown_10[0xe];
    u8 stride;
} TileTransfer;

void func_0806F5FC(TileTransfer *transfer, u8 width, u8 height)
{
    u16 index = 0;
    u16 row, column;

    for (row = 0; row < height; ++row) {
        u16 offset = transfer->stride * row;
        for (column = 0; column < width; ++column) {
            transfer->destination[offset + column] = transfer->source[index];
            ++index;
        }
    }
}
