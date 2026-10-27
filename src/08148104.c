#include "ffta.h"

/* 0x08148104..0x0814814A: 70 bytes. */
extern u16 func_08148384(u16 value, u16 first, u16 second, u16 third);

void func_08148104(const u16 *source, u16 *destination, u16 count, u16 adjustment)
{
    u16 index;
    for (index = 0; index < count; index++)
        destination[index] = func_08148384(source[index], adjustment,
                                           adjustment, adjustment);
}
