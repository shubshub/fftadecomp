#include "ffta.h"

/* Installed at 0x03005EAC by func_08002768. */
void func_08A38A60(u8 *destination, s32 size, u8 value)
{
    if (size <= 0)
        return;

    if ((u32)size >= sizeof(u32) && ((u32)destination & 3) == 0) {
        u32 fill = ((u32)value << 8) | value;
        fill |= fill << 16;

        do {
            *(u32 *)destination = fill;
            destination += sizeof(u32);
            size -= sizeof(u32);
        } while ((u32)size >= sizeof(u32));
        if (size <= 0)
            return;
    }
    do {
        *destination++ = value;
    } while (--size > 0);
}
