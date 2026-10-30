/* Target bytes (12):
 * 01 48 00 69 70 47 00 00 40 7f 00 02
 */
#include "ffta.h"

struct StateWordAt10 {
    u32 unknown_00[4];
    u32 value_10;
};

extern struct StateWordAt10 g_state_02007F40;

u32 func_0801E6A8(void)
{
    return g_state_02007F40.value_10;
}
