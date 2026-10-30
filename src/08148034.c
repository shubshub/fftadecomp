#include "ffta.h"

extern void *func_08147068(u16 first, u16 last, u16 amount, u16 setting,
                           u16 value, const void *data);

/* Target: complete [0x08148034, 0x08148084), 80 bytes.
 * 70b582b0069c0004000c051c0904090c1204160c1b041a0c2404240c691801390904
 * 090c0948814200d9011c0223002c00d10123009207980190281c321cfef7f9ff02b0
 * 70bc02bc08470000ff010000
 */
void *func_08148034(u16 first, u16 count, u16 amount, u16 value,
                    u16 enabled, const void *data)
{
    u16 last = first + count - 1;
    u16 setting;

    if (last > 511)
        last = 511;
    setting = 2;
    if (enabled == 0)
        setting = 1;
    return func_08147068(first, last, amount, setting, value, data);
}
