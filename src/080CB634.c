#include "ffta.h"

/* Complete [0x080CB634, 0x080CB63C): 8 bytes, 4 instructions.
 * Target bytes: 00 78 09 78 40 1A 70 47.
 */
s32 func_080CB634(const void *first, const void *second)
{
    return *(const u8 *)first - *(const u8 *)second;
}
