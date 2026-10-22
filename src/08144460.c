#include "ffta.h"

void *func_08144460(void *destination, s32 value, u32 length)
{
    u8 *bytes = destination;

    if (length > 3 && ((u32)bytes & 3) == 0) {
        u32 *words = (u32 *)bytes;
        u32 fill;

        value &= 0xFF;
        fill = (value << 8) | value;
        fill |= fill << 16;
        while (length > 15) {
            *words++ = fill;
            *words++ = fill;
            *words++ = fill;
            *words++ = fill;
            length -= 16;
        }
        while (length > 3) {
            *words++ = fill;
            length -= 4;
        }
        bytes = (u8 *)words;
    }
    while (length-- > 0) {
        *bytes++ = value;
    }
    return destination;
}
