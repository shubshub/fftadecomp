/* Target bytes (32):
 * 00 b5 05 48 05 4a 81 18 08 78 62 28 01 d8 01 30
 * 08 70 01 bc 00 47 00 00 00 00 00 02 68 1f 00 00
 */
#include "ffta.h"

struct StateByteAt1F68 {
    u8 unknown_0000[0x1F68];
    u8 value_1F68;
};

extern struct StateByteAt1F68 g_state_02000000;

void func_080CCBFC(void)
{
    if (g_state_02000000.value_1F68 <= 0x62)
        ++g_state_02000000.value_1F68;
}
