#include "oam_lists.h"

/* Complete [0x08001C34, 0x08001C4C): 24 bytes: 7 instructions, a padding
 * halfword and two literal words.
 * Target: 034a0449097889008918086070470000602f0003582f0003.
 */
void func_08001C34(s32 value)
{
    data_03002F60[data_03002F58] = value;
}
