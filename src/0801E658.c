/* Target bytes (16):
 * 02 48 40 78 c0 09 01 21 48 40 70 47 40 7f 00 02
 */
#include "ffta.h"

extern u8 g_state_02007F40[];

u8 func_0801E658(void)
{
    return (g_state_02007F40[1] >> 7) ^ 1;
}
