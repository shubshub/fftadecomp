#include "ffta.h"

typedef void (*BufferCopy0802BAF8)(void *destination, const void *source,
                                  u32 size);

extern BufferCopy0802BAF8 const data_0836D4BC[];

/* Complete [0x0802BAF8, 0x0802BB70): 120 bytes, 56 instructions. */
void func_0802BAF8(u8 *destination, const u8 *source)
{
    BufferCopy0802BAF8 const *callbacks = data_0836D4BC;
    s32 block;

    for (block = 0; block < 3; block++) {
        const u8 *sourceRight = source + 0x20;
        u8 *destinationRight = destination + 0x80;
        const u8 *sourceRow = source;
        u8 *destinationRow = destination;
        s32 row;

        for (row = 3; row >= 0; row--) {
            callbacks[0](destinationRow, sourceRow, 0x20);
            callbacks[0](destinationRight, sourceRight, 0x20);
            sourceRight += 0x40;
            destinationRight += 0x20;
            sourceRow += 0x40;
            destinationRow += 0x20;
        }
        source += 0x100;
        destination += 0x100;
    }
}
