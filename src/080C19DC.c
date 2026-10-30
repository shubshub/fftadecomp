/* Target bytes (20):
 * 02 49 03 4a 89 18 08 70 70 47 00 00 f8 01 01 02
 * d5 54 00 00
 */
#include "ffta.h"

struct StateByteAt54D5 {
    u8 unknown_0000[0x54D5];
    u8 value_54D5;
};

extern struct StateByteAt54D5 data_020101F8;

void func_080C19DC(u8 value)
{
    data_020101F8.value_54D5 = value;
}
