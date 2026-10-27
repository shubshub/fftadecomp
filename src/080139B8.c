#include "ffta.h"

/* Complete 0x080139B8..0x08013A5A: 162 bytes, 79 instructions. */
typedef unsigned long long u64;

void func_080139B8(u8 *buffer, int word_column, int source_block,
                   int nibble_shift)
{
    u32 *source = (u32 *)(buffer + 0x210) + source_block * 16;
    u32 *destination = (u32 *)(buffer + 0x10) + word_column;
    int shift = nibble_shift * 4;
    int row = (s8)buffer[0xb];
    int count;

    if (row >= 0) {
        for (count = 0; count < 16 && row < 16; count++, row++)
            *(u64 *)(destination + row * 8) |= (u64)source[count] << shift;
    } else {
        row = -row;
        for (count = 0; count < 16 && row < 16; count++, row++)
            *(u64 *)(destination + count * 8) |= (u64)source[row] << shift;
    }
}
