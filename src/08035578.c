#include "ffta.h"

/* Complete [0x08035578, 0x0803559E): 38 bytes, 19 instructions. */
void func_08035578(const u16 *source, u16 *destination, u32 count, u16 offset)
{
    u32 index;

    for (index = 0; index < count; index++) {
        u16 value = *source;

        *destination = value + offset;
        destination++;
        source++;
    }
}
