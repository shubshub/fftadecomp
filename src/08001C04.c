#include "oam_lists.h"

/* Complete [0x08001C04, 0x08001C1C): 24 bytes: 7 instructions, a padding
 * halfword and two literal words.
 * Target: 0349044800788000401800687047000068310003582f0003.
 */
s32 func_08001C04(void)
{
    return data_03003168[data_03002F58];
}
