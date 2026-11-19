#include "oam_lists.h"

/* Complete [0x08001BEC, 0x08001C04): 24 bytes: 7 instructions, a padding
 * halfword and two literal words.
 * Target: 034904480078800040180068704700002000000328000003.
 */
s32 func_08001BEC(void)
{
    return data_03000020[data_03000028];
}
