#include "oam_lists.h"

/* Complete [0x08001BBC, 0x08001BD4): 24 bytes: 7 instructions, a padding
 * halfword and two literal words.
 * Target: 03490448007880004018006870470000502c000328000003.
 */
s32 func_08001BBC(void)
{
    return data_03002C50[data_03000028];
}
