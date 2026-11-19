#include "oam_lists.h"

/* Complete [0x08001BD4, 0x08001BEC): 24 bytes: 7 instructions, a padding
 * halfword and two literal words.
 * Target: 03490448007880004018006870470000602f0003582f0003.
 */
s32 func_08001BD4(void)
{
    return data_03002F60[data_03002F58];
}
