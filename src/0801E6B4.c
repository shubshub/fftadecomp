/* Target bytes (32):
 * 00 b5 00 06 00 28 05 d1 01 48 40 69 04 e0 00 00
 * 40 7f 00 02 01 48 80 69 02 bc 08 47 40 7f 00 02
 */
#include "ffta.h"

struct StateWordSelection {
    u32 unknown_00[5];
    u32 value_14;
    u32 value_18;
};

extern struct StateWordSelection g_state_02007F40;

u32 func_0801E6B4(u8 selector)
{
    if (selector)
        return g_state_02007F40.value_18;
    return g_state_02007F40.value_14;
}
