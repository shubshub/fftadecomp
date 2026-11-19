#include "oam_lists.h"

/* Complete [0x08001C64, 0x08001C7C): 24 bytes: 7 instructions, a padding
 * halfword and two literal words.
 * Target: 034a044909788900891808607047000068310003582f0003.
 */
void func_08001C64(s32 value)
{
    data_03003168[data_03002F58] = value;
}
