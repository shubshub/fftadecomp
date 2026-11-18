#include "ffta.h"

/* The boot copy installs this routine at the Thumb target in 0x0836D4BC. */
void func_08A38A9C(void *destination, const void *source, u32 length)
{
    u8 *out = destination;
    const u8 *in = source;

    if ((s32)length <= 0)
        return;

    if (length >= sizeof(u32) && ((u32)out & 3) == 0 && ((u32)in & 3) == 0) {
        u32 *out_words = (u32 *)out;
        const u32 *in_words = (const u32 *)in;
        do {
            *out_words++ = *in_words++;
            length -= sizeof(u32);
        } while (length >= sizeof(u32));
        out = (u8 *)out_words;
        in = (const u8 *)in_words;
        if ((s32)length <= 0)
            return;
    }
    do {
        *out++ = *in++;
        --length;
    } while ((s32)length > 0);
}
