#include "ffta.h"

extern const u16 data_083937B2[];
extern u8 func_080C9540(u16 bitIndex);

/* Complete [0x08050C38, 0x08050C74): 60 bytes, 24 instructions.
 * Target: f0b500260b4c071c052520884f2805d1094878f079fc0006002802d0208801c7
 *         01360234013d002defda301cf0bc02bc08470000b237390807020000
 */
u32 func_08050C38(u32 *output)
{
    u32 count = 0;
    const u16 *entry = data_083937B2;
    u32 *destination = output;
    s32 remaining = 5;

    do {
        if (*entry != 0x4F || func_080C9540(0x207)) {
            *destination++ = *entry;
            count++;
        }
        entry++;
        remaining--;
    } while (remaining >= 0);
    return count;
}
