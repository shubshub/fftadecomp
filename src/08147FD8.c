#include "ffta.h"

extern void *func_08146FB8(u16 first, u16 last, u16 amount, u16 setting,
                           u16 value);

/* Target: complete [0x08147FD8, 0x08148034), 92 bytes.
 * f0b581b0069c0004000c061c0904090c1204150c1b041f0c2404220c71180139
 * 09040c0c0c48844200d9041c0223002a00d101232a04111401204042814201d1
 * 04200343120c0097301c211cfef7c8ff01b0f0bc02bc0847ff010000
 */
void *func_08147FD8(u16 first, u16 count, s16 amount, u16 value, u16 enabled)
{
    u16 last = first + count - 1;
    u16 setting;

    if (last > 511)
        last = 511;
    setting = enabled == 0 ? 1 : 2;
    if (amount == -1)
        setting |= 4;
    return func_08146FB8(first, last, amount, setting, value);
}
