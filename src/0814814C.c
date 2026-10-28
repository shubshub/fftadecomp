#include "ffta.h"

extern u16 func_08148384(u16 value, u16 first, u16 second, u16 third);

/* Complete [0x0814814C, 0x081481AA): 94 bytes, 46 instructions. */
void func_0814814C(const u16 *source, u16 *destination, u16 count,
                   u16 first, u16 second, u16 third)
{
    u16 index;

    for (index = 0; index < count; index++)
        destination[index] = func_08148384(source[index], first, second, third);
}
