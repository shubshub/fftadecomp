#include "ffta.h"

extern u16 func_08147958(u16 color, u8 amount);

/* Complete [0x08148318, 0x0814835A): 66 bytes, 32 instructions. */
void func_08148318(const u16 *source, u16 *destination, u16 count, u8 amount)
{
    u16 index;

    for (index = 0; index < count; index++)
        destination[index] = func_08147958(source[index], amount);
}
