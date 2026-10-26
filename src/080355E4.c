#include "ffta.h"

/* Complete target: [0x080355E4, 0x08035636), 82 bytes. */
void func_080355E4(const u16 *source, u16 *destination, u32 height,
                   u16 width, u16 stride, u16 offset)
{
    u32 row;
    u32 column;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++)
            destination[column] = offset + *source++;
        destination += stride;
    }
}
