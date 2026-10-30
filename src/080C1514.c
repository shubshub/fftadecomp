/* Target bytes (20):
 * 02 48 03 49 40 18 00 88 70 47 00 00 f8 01 01 02
 * be 54 00 00
 */
#include "ffta.h"

struct StateHalfwordAt54BE {
    u8 unknown_0000[0x54BE];
    u16 value_54BE;
};

extern struct StateHalfwordAt54BE data_020101F8;

u16 func_080C1514(void)
{
    return data_020101F8.value_54BE;
}
