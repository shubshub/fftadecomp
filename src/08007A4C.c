/* 0x08007A4C - 20 bytes
 * Target: 0006 0349 c00d 4018 0021 405e 7047 0000 68951408
 */
#include "ffta.h"

extern const s16 g_table_08149568[];

s32 func_08007A4C(u8 index)
{
    return g_table_08149568[index];
}
