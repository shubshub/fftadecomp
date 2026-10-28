#include "ffta.h"

typedef union TileEntry {
    struct {
        u16 tile : 10;
        u16 horizontal_flip : 1;
        u16 vertical_flip : 1;
        u16 palette : 4;
    } fields;
    u16 value;
} TileEntry;

/* 0x08016A08: 144 bytes, 67 instructions. Draw the horizontal frame edges. */
void func_08016A08(u16 *buffer, u8 width, u8 height, u8 stride)
{
    if (width > 1 && height > 1) {
        TileEntry corner = {{0x32, 0, 0, 0xB}};
        u16 tile = corner.value;
        u16 right = width - 1;
        u16 bottom_offset = (height - 1) * stride;
        u16 *top_right;
        u16 *bottom;
        s32 x;

        buffer[0] = tile;
        top_right = right + buffer;
        top_right[0] = tile + 0x400;
        bottom = bottom_offset + buffer;
        bottom[0] = tile + 0x800;
        top_right[bottom_offset] = tile + 0xC00;
        for (x = 1; x < width - 1; ++x) {
            buffer[x] = tile + 1;
            bottom[x] = tile + 0x801;
        }
    }
}
