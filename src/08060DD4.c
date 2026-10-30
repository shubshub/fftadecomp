/* Target bytes (12):
 * 01 48 00 68 80 7d 70 47 4c f4 00 02
 */
#include "ffta.h"

struct ObjectStateAt16 {
    u8 unknown_00[0x16];
    u8 value_16;
};

extern struct ObjectStateAt16 *data_0200F44C;

u8 func_08060DD4(void)
{
    return data_0200F44C->value_16;
}
