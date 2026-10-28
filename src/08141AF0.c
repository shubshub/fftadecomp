#include "ffta.h"

/* Complete [0x08141AF0, 0x08141B12): 34 bytes, 17 instructions. */
void func_08141AF0(const u8 *source, u8 *destination, u32 count)
{
    u32 remaining = count - 1;
    if (count != 0) {
        do {
            *destination++ = *source++;
        } while (remaining-- != 0);
    }
}
