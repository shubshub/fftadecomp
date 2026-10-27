#include "ffta.h"

extern u16 func_081483EC(u16 value, u16 first, u16 second, u16 third);

/* Complete [0x08148214, 0x08148272): 94 bytes, 46 instructions. */
void func_08148214(const u16 *source, u16 *destination, u16 count,
                   u16 first, u16 second, u16 third)
{
    u16 index;

    for (index = 0; index < count; index++)
        destination[index] = func_081483EC(source[index], first, second, third);
}
