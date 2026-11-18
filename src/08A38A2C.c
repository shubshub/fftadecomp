#include "ffta.h"

/* 0x08A38A2C..0x08A38A5E, 50 bytes. The installer at 08002768 copies
 * this body to 03005E78. Callers load its Thumb pointer from 0836D4B8.
 * The byte count has a signed entry guard and an unsigned word-loop bound.
 */
void func_08A38A2C(void *destination, u32 size)
{
    u8 *cursor = destination;

    if ((s32)size <= 0)
        return;

    if (size >= sizeof(u32) && ((u32)cursor & 3) == 0) {
        do {
            *(u32 *)cursor = 0;
            cursor += sizeof(u32);
            size -= sizeof(u32);
        } while (size >= sizeof(u32));
        if ((s32)size <= 0)
            return;
    }

    do {
        *cursor++ = 0;
        size--;
    } while ((s32)size > 0);
}
