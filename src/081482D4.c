#include "ffta.h"

/* 0x081482D4..0x08148316: 66 bytes. */
extern u16 func_081478DC(u16, u8);

void func_081482D4(const u16 *source, u16 *destination, u16 count, u8 mode)
{
    u16 i;

    for (i = 0; i < count; ++i)
        destination[i] = func_081478DC(source[i], mode);
}
