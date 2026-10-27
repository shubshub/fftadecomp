#include "ffta.h"

extern u16 func_08147830(u16 color, u16 reference, u8 amount, u8 mode);

/* Complete [0x08148274, 0x081482D2): 94 bytes, 46 instructions. */
void func_08148274(const u16 *source, u16 *destination, u16 count,
                  u16 reference, u8 amount, u8 mode)
{
    u16 index;

    for (index = 0; index < count; index++)
        destination[index] = func_08147830(source[index], reference, amount, mode);
}
