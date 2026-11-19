#include "oam_lists.h"

/* Complete [0x08001C1C, 0x08001C34): 24 bytes: 7 instructions, a padding
 * halfword and two literal words.
 * Target: 034a0449097889008918086070470000502c000328000003.
 */
void func_08001C1C(s32 value)
{
    data_03002C50[data_03000028] = value;
}
