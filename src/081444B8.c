#include "ffta.h"

u32 func_081444B8(const void *input)
{
    const u8 *bytes = input;
    const u8 *start = bytes;

    if (((u32)bytes & 3) == 0) {
        const u32 *words = (const u32 *)bytes;

        while (((*words - 0x01010101) & ~*words & 0x80808080) == 0) {
            words++;
        }
        bytes = (const u8 *)words;
    }
    while (*bytes != 0) {
        bytes++;
    }
    return bytes - start;
}
