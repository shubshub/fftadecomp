/* 0x0800717C - 16 bytes
 * Target: 0c39 8a79 c879 0002 1043 8000 0c38 7047
 */
#include "ffta.h"

u32 func_0800717C(void *owner, const u8 *payload)
{
    const u8 *block = payload - 12;
    u32 low = block[6];
    u32 size = (block[7] << 8) | low;

    return size * 4 - 12;
}
