#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54D4];
    u8 unknown_54D4_lo : 4;
    u8 unknown_54D4_hi : 4;
} State080C19BC;

extern State080C19BC data_020101F8;

/* Target bytes [080C19BC, 080C19DC):
 * 00 06 05 4A 05 49 52 18 00 0D 13 78 0F 21 19 40
 * 01 43 11 70 70 47 00 00 F8 01 01 02 D4 54 00 00.
 */
void func_080C19BC(u8 value)
{
    data_020101F8.unknown_54D4_hi = value;
}
