#include "ffta.h"

extern const u8 g_table_08394778[];

/* 080CCAD8..080CCAE8: 16 bytes, including literal pool.
 * 0006000e014940180078704778473908
 */
u8 func_080CCAD8(u8 index)
{
    return g_table_08394778[index];
}
