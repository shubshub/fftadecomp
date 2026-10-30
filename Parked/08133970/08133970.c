#include "ffta.h"

extern const u8 data_083A87B0[];

/* Target bytes [08133970, 08133988):
 * 00 06 00 0E 03 4A 41 00 09 18 89 00 04 32 89 18
 * 08 78 70 47 B0 87 3A 08.
 */
u8 func_08133970(u8 index)
{
    return data_083A87B0[index * 12 + 4];
}
