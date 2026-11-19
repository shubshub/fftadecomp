#include "oam_lists.h"

/* Complete [0x08001C4C, 0x08001C64): 24 bytes: 7 instructions, a padding
 * halfword and two literal words.
 * Target: 034a04490978890089180860704700002000000328000003.
 */
void func_08001C4C(s32 value)
{
    data_03000020[data_03000028] = value;
}
