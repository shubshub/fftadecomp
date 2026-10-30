/* Target bytes (12):
 * 01 48 c0 8b 70 47 00 00 40 7f 00 02
 */
#include "ffta.h"

struct StateHalfwordAt1E {
    u16 unknown_00[15];
    u16 value_1E;
};

extern struct StateHalfwordAt1E g_state_02007F40;

u16 func_0801E6E4(void)
{
    return g_state_02007F40.value_1E;
}
